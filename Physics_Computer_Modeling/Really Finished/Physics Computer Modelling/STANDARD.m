%Class:
%Topic: 

%-----------preparing window----------------------------------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "  ");                                                           %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["  "];                                                                   %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("  ",'fontsize',[17]);                                              %labeling y axis
a : ylabel ("  ",'fontsize',[17]);                                              %labeling x axis
a : zlabel ("  ",'fontsize',[17]);                                              %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system