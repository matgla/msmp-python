#!/usr/bin/bash

mkdir -p venv
virtualenv venv

source venv/bin/activate
git clone https://github.com/gccxml/pygccxml
cd pygccxml
python3 setup.py install
pip3 install pyplusplus
python3 $1
cp msmp_core.cpp ../msmp_core.cpp
echo "Generation finished!"