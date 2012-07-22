#!/bin/sh

# custom build steps for visualnews
# created by (c) ch0kee

filename="test.vnsession"

srcpath="$1$filename"
destpath="`pwd`/$filename"

echo "source file: $srcpath"
echo "destination path: $destpath"

cp $srcpath $destpath
result_of_copy=$?

echo -n "result of copy: "
[ $result_of_copy -eq 0 ] && echo "SUCCESS" || echo "FAIL"

exit $result_of_copy