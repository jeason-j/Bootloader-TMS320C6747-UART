::====================================================================================================
:: Description:                 FH Ӧ�ó�������ļ�,���������������ֹͣ
::                              
:: Author:                      YanDengxue, Fiberhome-Fuhua
::                              
:: History:                     Created at 2011.03.22
::                              
:: Version:                     1.00
::
:: Rev History:  
::       <Author>        <Data>        <Version>        <Description>
::     YanDengxue       2011-03-22       1.00              Create
::====================================================================================================
@set PATH=%CD%\..\Tools\CGTools\bin;%CD%\..\Tools;D:\FHFiles\MSYS\mingw\bin;%SystemRoot%\system32
@set C6X_C_DIR=%CD%\..\Tools\CGTools\include;%CD%\..\Tools\CGTools\lib

@make all 
@set CMOPILE_RESULT=%ERRORLEVEL%
@if not "0"=="%CMOPILE_RESULT%" goto SHOW_COMPILE_ERRORS

@goto skip

::------------------------------------------------------------------------------
:: ���������ʾ������ʾ
::------------------------------------------------------------------------------
:SHOW_COMPILE_ERRORS
@echo ==========================================================================
@echo *******************��������з��ִ���,������ȷ��!лл!********************
@echo *******************�������,�벦��:13995508371!***************************
@echo ==========================================================================
@pause


::==============================================================================
:: ����
::==============================================================================
:skip