import sys 
import vcf 
import re
import os 
import hashlib
from peewee import * 

filename = os.path.abspath(sys.argv[1])

dirpath  = os.path.dirname(os.path.realpath(filename))
basename = os.path.splitext(os.path.basename(filename))[0]
dbname   = os.path.join(dirpath,basename+".db")

try:
	os.remove(dbname)
except : 
	pass

db = SqliteDatabase(dbname)


# ================= MODEL =============================
class Project(Model):
	dbname        = CharField()
	filename      = CharField()
	md5sum        = CharField()


class Variant(Model):
	chrom = CharField()
	pos   = IntegerField()
	ref   = CharField()
	alt   = CharField()
	class Meta:
		database = db 
		db_table = "variants"

class Field(Model):
	colname     = CharField()
	description = CharField()
	class Meta:
		database = db
		db_table = "fields"

class Annotation(Model):
	variant = ForeignKeyField(Variant, related_name='variant')
	class Meta:
		database = db
		db_table = "annotations"

class Sample(Model):
	name = CharField()
	class Meta:
		database = db 
		db_table = "samples"

class Genotype(Model):
	sample   = ForeignKeyField(Sample, related_name="sample")
	variant  = ForeignKeyField(Sample, related_name="variant")
	genotype = IntegerField() 


db.connect()
db.create_tables([Variant, Field,Sample, Project], safe = True)

# ================= IMPORT =============================

def import_variant(filename):
	print("Creating", dbname) 
	# Create project 
	prj = Project()
	prj.dbname   = dbname
	prj.filename = filename 
	prj.md5sum   = hashlib.md5(open(filename, 'rb').read()).hexdigest()
	prj.save()
	# Start reading VCF file 
	SPECIAL_FIELDS = ("ANN","LOF","NMD")
	reader = vcf.Reader(open(filename,'r'))
	#  PARSE HEADERS AND CREATE ANNOTATION TABLE ACCORDING FIELDS NUMBER
	for info in reader.infos:
		if info in SPECIAL_FIELDS:
			desc = reader.infos[info].desc
			bloc = re.findall(r"'(.+)'", desc)
			fields = [i.strip() for i in bloc[0].split("|")]
			for i in range(len(fields)):
				key = info +"_" + str(i+1)
				f = Field(colname = key, description = fields[i])
				f.save()
				# Append new columns no annotation 
				new_col = CharField(null=True)
				new_col.add_to_class(Annotation, key)
			# Create annotation table
		else:
			key = info 
			f   = Field(colname = key, description = reader.infos[info].desc)
			f.save()
			new_col = CharField(null=True)
			new_col.add_to_class(Annotation, key)
	Annotation.create_table()

	# IMPORT VARIANT AND ANNOTATION DATA
	with db.transaction():
		for record in reader:
			for alt_i in range(len(record.ALT)):
				variant     = Variant.create(chrom = record.CHROM, pos = record.POS, ref = record.REF, alt = record.ALT[alt_i] )
				ann         = Annotation()
				ann.variant = variant

				for k in record.INFO.keys():
					if k in SPECIAL_FIELDS:
						raw_ann = record.INFO[k]
						i = 1
						for value in raw_ann[0].split("|"):
							key = k+"_"+str(i)
							setattr(ann,key,value)
							i+=1

					else:
						if isinstance(record.INFO[k], list):
							if len(record.ALT) == len(record.INFO[k]):
								setattr(ann,k, record.INFO[k][alt_i])
							else:
								setattr(ann,k, record.INFO[k][0])
						else:
							setattr(ann,k, record.INFO[k])
				ann.save()

# ================= IMPORT =============================

import_variant(filename)

