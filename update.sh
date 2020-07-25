#!/bin/bash
git pull
git add .
timenow=$(date)
git commit -m "${timenow}"
git push
