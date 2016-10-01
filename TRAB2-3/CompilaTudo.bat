@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TestePeca.exe

del *.obj
nmake /Ftestepeca.make 

copy  *.err  tudo.err

notepad tudo.err

popd
