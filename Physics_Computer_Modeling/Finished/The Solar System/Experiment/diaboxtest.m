%Experiment for next version

f=figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Heliocentric"); %Creating Window

b3 = uicontrol (f, "style", "radiobutton","string", "Not in the group","Position", [ 10 720 150 30 ]);



b4 = uicontrol (f,"string", "Not in the group","Position", [ 10 520 150 30 ],'buttondownfcn',"heliocentricxp");



%waitforbuttonpress ()
%wait()
%if b3==true
  
  %printf("success")
  
%endif

%axes('position',[.1 .1 .8 .8],'color',[1 1 1], 'xlim',[-13 13],'ylim',[-13 13]);  %Creating Axis


%ButtonDownFcn

%if b3==true
  
  %printf("success")
  
%endif