#!/bin/bash
if [ "$#" -ne 1 ]; then
	echo "$(tput setaf 1)usage is 'new-tag'$(tput sgr0)"
	exit 1
fi
echo "$(tput setaf 3)Getting last tag...$(tput sgr0)"
ltag=`git describe --abbrev=0 --tags`
echo $ltag
echo "$(tput setaf 3)Updating README...$(tput sgr0)"
sed -i -e "s/$ltag/$1/" README.md
echo "$(tput setaf 3)Updating Podspec...$(tput sgr0)"
sed -i -e "s/$ltag/$1/" vlc-sdk.podspec
echo "$(tput setaf 3)Tagging & Bagging...($1)$(tput sgr0)"
git add . --all
git commit -m "$1"
git tag "$1"
echo "$(tput setaf 3)Pushing + Tags...$(tput sgr0)"
git push
git push --tags
echo "$(tput setaf 2)Done.$(tput sgr0)"
