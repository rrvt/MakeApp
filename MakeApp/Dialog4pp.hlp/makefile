

Dialog4pp.chm : *.htm Dialog4pp.hhp Dialog4pp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" Dialog4pp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist Dialog4pp.chm del /f Dialog4pp.chm


$(TgtFolder)/Dialog4pp.chm : Dialog4pp.chm
  copy $(MAKEDIR)\Dialog4pp.chm  $(MAKEDIR)\..\$(TgtFolder)\Dialog4pp.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist Dialog4pp.chm del /f Dialog4pp.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/Dialog4pp.chm

