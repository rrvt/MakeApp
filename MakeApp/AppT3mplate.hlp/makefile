

AppT3mplate.chm : *.htm AppT3mplate.hhp AppT3mplate.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AppT3mplate


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist AppT3mplate.chm del /F AppT3mplate.chm


Release/AppT3mplate.chm : AppT3mplate.chm
  copy $(MAKEDIR)\AppT3mplate.chm  $(MAKEDIR)\..\Release\AppT3mplate.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist AppT3mplate.chm del /F AppT3mplate.chm
  cd $(MAKEDIR)


Debug/AppT3mplate.chm : AppT3mplate.chm
  copy $(MAKEDIR)\AppT3mplate.chm  $(MAKEDIR)\..\Debug\AppT3mplate.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist AppT3mplate.chm del /F AppT3mplate.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/AppT3mplate.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/AppT3mplate.chm


