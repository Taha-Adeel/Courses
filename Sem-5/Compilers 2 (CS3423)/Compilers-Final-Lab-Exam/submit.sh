#!/bin/bash
rollno=$1
if [ -z $rollno ]
then echo "Enter Registration Number...Exiting"
	exit
fi
mv RollNo_LabExam ${rollno}_LabExam
make -C ${rollno}_LabExam clean
tar -cvzf ${rollno}_LabExam.tar.gz ${rollno}_LabExam
