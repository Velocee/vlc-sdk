#!/bin/bash
# h file
echo "Searching .h file..."
hfile=($(find ../velocee-dev-ios/iPhoneSDK/VlcSdk/VlcSdk/ -name "VlcSdk.h" | xargs ls -l))
echo ${hfile[@]}
if diff ./VlcSdk.h ${hfile[8]}; then
	echo 'files are equal.'
fi
read -p "$(tput setaf 3)Enter to continue & copy, Ctrl-C quits.$(tput sgr0)" ui
find ../velocee-dev-ios/iPhoneSDK/VlcSdk/VlcSdk/ -name "VlcSdk.h" | xargs ls | xargs -I{} cp {} .
if [[ $? -ne 0 ]]
then
    echo "$(tput setaf 1)Error copying h file$(tput sgr0)"
	exit $?
fi
echo "$(tput setaf 2)Ok$(tput sgr0)"
# bundle
echo "Searching for bundle..."
bfile=($(find /Users/elibabila/Library/Developer/Xcode/DerivedData -type d -name "VlcSdkRes.bundle" | xargs ls -ltrd | tail -1))
echo ${bfile[@]}
diff -arq ./VlcSdkRes.bundle ${bfile[8]}
read -p "$(tput setaf 3)Enter to continue & copy (will remove local first), Ctrl-C quits.$(tput sgr0)" ui
rm -Rf ./VlcSdkRes.bundle
find /Users/elibabila/Library/Developer/Xcode/DerivedData -type d -name "VlcSdkRes.bundle" | xargs ls -ltrd | tail -1 | grep -o "/Users/.*" | xargs -I{} cp -R {} .
if [[ $? -ne 0 ]]
then
    echo "$(tput setaf 1)Error copying bundle $(tput sgr0)"
	exit $?
fi
echo "$(tput setaf 2)Ok$(tput sgr0)"
# libvlcsdk
echo "Searching for sdk file..."
echo $(find /Users/elibabila/Library/Developer/Xcode/DerivedData -name "libVlcSdk.a" | xargs ls -ltr | grep universal | tail -1)
read -p "$(tput setaf 3)Enter to continue & copy, Ctrl-C quits.$(tput sgr0)" ui
find /Users/elibabila/Library/Developer/Xcode/DerivedData -name "libVlcSdk.a" | xargs ls -ltr | grep universal | tail -1 | grep -o "/Users/.*" | xargs -I{} cp {} .
if [[ $? -ne 0 ]]
then
    echo "$(tput setaf 1)Error copying bundle $(tput sgr0)"
	exit $?
fi
echo "$(tput setaf 2)Ok$(tput sgr0)"
echo "$(tput setaf 2)Done.$(tput sgr0)"
