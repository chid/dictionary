#!/bin/sh
TESTN=$(cat<<EOF
ok
EOF
)
TESTNE=$(cat<<EOF
ok
EOF
)

echo $TESTN > testd
echo $TESTNE > teste
./word < testd > testr
diff testr teste

# if the above returns anything other than 0 then there's been an error
