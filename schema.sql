
DROP TABLE IF EXISTS `filenames`;
		
CREATE TABLE `filenames` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `filename`  TEXT
);

-- ---
-- Table 'variants'
-- 
-- ---

DROP TABLE IF EXISTS `variants`;

CREATE TABLE `variants` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `bin` INTEGER DEFAULT 0,
  `chrom` TEXT,
  `pos` INTEGER,
  `ref` TEXT,
  `alt` TEXT,
  UNIQUE(  `chrom` ,  `pos` , `ref` ,  `alt` ) ON CONFLICT IGNORE
); 

CREATE INDEX idx_variant ON variants(`id`);
-- ---
-- Table 'sample_has_variant'
-- 
-- ---

DROP TABLE IF EXISTS `sample_has_variant`;
		
CREATE TABLE `sample_has_variant` (
  `sample_id` INTEGER,
  `variant_id` INTEGER,
  `genotype` INTEGER

);

-- ---
-- Table 'samples'
-- 
-- ---

DROP TABLE IF EXISTS `samples`;
		
CREATE TABLE `samples` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `name` TEXT,
  `filename_id`INTEGER,
   FOREIGN KEY(`filename_id`) REFERENCES filenames(`id`)

);
-- ---
-- Table 'annotations'
--
-- ---
DROP TABLE IF EXISTS `annotations`;

-- ---
-- Table 'projets'
-- 
-- ---

DROP TABLE IF EXISTS `projets`;
		
CREATE TABLE `projets` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `name` TEXT,
  `build` TEXT
);

-- ---
-- Table 'fields'
-- 
-- ---

DROP TABLE IF EXISTS `fields`;
		
CREATE TABLE `fields` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `name` TEXT UNIQUE,
  `description` TEXT,
  `type` INTEGER
);

-- ---
-- Table 'phenotypes'
-- 
-- ---

DROP TABLE IF EXISTS `phenotypes`;
		
CREATE TABLE `phenotypes` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `id_samples` INTEGER,
  FOREIGN KEY(`id_samples`) REFERENCES samples(`id`)
);

-- ---
-- Table 'genotypes'
-- 
-- ---

DROP TABLE IF EXISTS `genotypes`;
		
CREATE TABLE `genotypes` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `geno_field_id` INTEGER,
  `value` TEXT,
  FOREIGN KEY(`geno_field_id`) REFERENCES geno_fields(`id`)

);

-- ---
-- Table 'geno_fields'
-- 
-- ---

DROP TABLE IF EXISTS `geno_fields`;
		
CREATE TABLE `geno_fields` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `name` TEXT,
  `description` TEXT,
  `type` INTEGER

);

-- ---
-- Table 'tables'
-- 
-- ---

DROP TABLE IF EXISTS `tables`;
		
CREATE TABLE `tables` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `name` TEXT,
  `count` INTEGER,
  `description` TEXT

);

-- ---
-- Table 'table_has_variant'
-- 
-- ---

DROP TABLE IF EXISTS `table_has_variant`;
		
CREATE TABLE `table_has_variant` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
  `table_id` INTEGER,
  `variant_id` INTEGER,
  FOREIGN KEY(`table_id`) REFERENCES tables(`id`),
  FOREIGN KEY(`variant_id`) REFERENCES variants(`id`)

);
