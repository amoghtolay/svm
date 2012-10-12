#!/bin/sh

rm -v GLPK_Files/one-vs-one/hyperplaneClass_glpk
rm -v GLPK_Files/one-vs-one/accuracy_glpk
rm -v GLPK_Files/one-vs-one/margin_glpk
rm -v GLPK_Files/one-vs-one/spans_glpk
rm -v GLPK_Files/one-vs-one/nSV_glpk
mv -v GLPK_Files/one-vs-one/crossEfficiency_glpk.txt GLPK_Files/one-vs-one/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/one-vs-one/output_efficiencies.vsone.txt
rm -v GLPK_Files/one-vs-one/avg_efficiencies.vsone.txt

rm -v GLPK_Files/one-vs-all/hyperplaneClass_glpk
rm -v GLPK_Files/one-vs-all/accuracy_glpk
rm -v GLPK_Files/one-vs-all/margin_glpk
rm -v GLPK_Files/one-vs-all/spans_glpk
rm -v GLPK_Files/one-vs-all/nSV_glpk
mv -v GLPK_Files/one-vs-all/crossEfficiency_glpk.txt GLPK_Files/one-vs-all/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/one-vs-all/output_efficiencies.vsall.txt

rm -v GLPK_Files/dense/hyperplaneClass_glpk
rm -v GLPK_Files/dense/accuracy_glpk
rm -v GLPK_Files/dense/margin_glpk
rm -v GLPK_Files/dense/spans_glpk
rm -v GLPK_Files/dense/nSV_glpk
mv -v GLPK_Files/dense/crossEfficiency_glpk.txt GLPK_Files/dense/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/dense/output_efficiencies.dense.txt

rm -v GLPK_Files/sparse/hyperplaneClass_glpk
rm -v GLPK_Files/sparse/accuracy_glpk
rm -v GLPK_Files/sparse/margin_glpk
rm -v GLPK_Files/sparse/spans_glpk
rm -v GLPK_Files/sparse/nSV_glpk
mv -v GLPK_Files/sparse/crossEfficiency_glpk.txt GLPK_Files/sparse/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/sparse/output_efficiencies.sparse.txt
