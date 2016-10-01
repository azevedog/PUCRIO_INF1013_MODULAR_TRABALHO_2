@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteTabuleiro.exe

del *.obj
nmake /FTesteTabuleiro.make 

copy  *.err  tudo.err

notepad tudo.err

popd
