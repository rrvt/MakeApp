

AppT3mplate.chm : *.htm AppT3mplate.hhp AppT3mplate.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AppT3mplate


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist AppT3mplate.chm del /F AppT3mplate.chm


$(TgtFolder)/AppT3mplate.chm : AppT3mplate.chm
  copy $(MAKEDIR)\AppT3mplate.chm  $(MAKEDIR)\..\$(TgtFolder)\AppT3mplate.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist AppT3mplate.chm del /F AppT3mplate.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/AppT3mplate.chm


