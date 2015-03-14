#!/bin/sh
./.linux.sh 
%cp%=for /f %%i in ("%0") do set curpath=%%~dpi
call=%curpath%.windows.cmd %curpath% 

