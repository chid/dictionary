make -s
./word $1 < word_example.txt | tee -a chid_output
./dict $1 < word_example.txt | tee -a ref_output
echo "Diff"
diff ref_output chid_output
# gdb ./word
