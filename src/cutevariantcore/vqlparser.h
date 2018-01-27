#ifndef VQLCOMPILER_H
#define VQLCOMPILER_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>



using namespace boost::spirit;

/*
Exemple of query :
SELECT chr, pos, ref, ann.gene_name FROM variant
SELECT chr, pos, ref, sample["boby"].gt FROM variant
SELECT chr, pos, ref, ann.gene_name FROM variant WHERE pos = 3
SELECT chr, pos, ref, sample["boby"].gt FROM variant INSIDE bed

*/

using namespace std;


struct VqlResult {
   std::vector<std::string> selectData;
   std::string fromData;
   std::string whereData;
   std::string regionData;

};

BOOST_FUSION_ADAPT_STRUCT
(
    VqlResult,
    selectData,
    fromData,
    whereData,
    regionData
);

class VqlParser
{
public:
    VqlParser();
    bool parse(const string& source);

    const string& source() const;
    const string& tableName() const;
    const vector<string>& columns() const;
    const string& conditions() const;
    const string& region() const;


private:
    string mSource;
    VqlResult mResult;

};


std::ostream &operator<<(std::ostream& os, VqlParser& c);

#endif // VQLCOMPILER_H
