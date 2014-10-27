#!/bin/bash
if [ "$#" -ne 1 ]; then
	echo "$(tput setaf 1)usage is 'new-tag'$(tput sgr0)"
	exit 1
fi
echo "$(tput setaf 3)Tagging & Bagging...($1)$(tput sgr0)"
git add . --all
git commit -m "$1"
git tag "$1"
echo "$(tput setaf 3)Pushing + Tags...$(tput sgr0)"
git push
git push --tags
echo "$(tput setaf 2)Done.$(tput sgr0)"
