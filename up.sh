rm -rv mf
mkdir mf
cp -v words.c dictionary.c dictionary.h dictionary_type.h mudflap tc* mf
tar -cf mf.tar mf
echo put mf.tar | sftp cpen274@cse
