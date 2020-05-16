#!/bin/zsh

echo " -- 185 --"

echo "10 10
151 92 131 165 197 30 149 199 19 85
13 15 26 12 11 22 11 35 23 21" | ./soln;

echo " -- 0 -- ";

echo "2 5
5 5
4 4" | ./soln;

echo  " -- 12 -- ";

curl -X GET "https://hr-testcases-us-east-1.s3.amazonaws.com/88853/input00.txt?AWSAccessKeyId=AKIAJ4WZFDFQTZRGO3QA&Expires=1589642530&Signature=FErDmvcO3EiqFaqEj3Q0ILvLX90%3D&response-content-type=text%2Fplain" | ./soln;

echo " -- 37021537 -- ";

curl -X GET "https://hr-testcases-us-east-1.s3.amazonaws.com/88853/input09.txt?AWSAccessKeyId=AKIAJ4WZFDFQTZRGO3QA&Expires=1589641683&Signature=B8humErIAMIUi9vP3iFZaZVdvSM%3D&response-content-type=text%2Fplain" | ./soln;
