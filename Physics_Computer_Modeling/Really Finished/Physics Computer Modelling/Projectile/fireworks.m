%firework, started 21.02.19

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Fireworks");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[.1 .1 .1],'fontsize',[12]);             %Creating Axis
txt = [ "Fireworks"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
%a : ylabel ("Y in m",'fontsize',[17]);                                          %labeling y axis
%a : xlabel ("X in m",'fontsize',[17]);                                          %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
%view(-90,0);
drawnow;    
%--------------constants-------------------------
g=9.81;                                                           %setting g
x01=y01=x02=y02=x03=y03=x04=y04=x05=y05=x06=y06=0;                                                       %initializing

z2=z02=z3=z03=z4=z04=z5=z05=z6=z06=0;

fi01=45;
v01=5;

fi02=65;
v02=10;

fi03=135;
v03=5;

fi04=65;
v04=10;

fi05=75;
v05=12;

fi06=105;
v06=10;

%---------------limit calculation-----------------
fi1=fi01/(360/(2*pi));
fi2=fi02/(360/(2*pi));
fi3=fi03/(360/(2*pi));
fi4=fi04/(360/(2*pi));
fi5=fi05/(360/(2*pi));
fi6=fi06/(360/(2*pi));
%lxp=2.7*((v0.^2.*sin(2.*fi))./g);                                %calculating x limit
%lyp=((v0.^2.*sin(fi).^2)/(2.*g)).*1.15;                           %calculating y limit
axis('equal',[-5.5 8 -5 10 -30 25]); 
%view(30,190);                                     %setting axis limits
drawnow;                                                          %Drawing it now
h_proj1=line(0,0,'marker','*','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
h_proj2=line(0,0,'marker','*','color',[0 1 0],'markerfacecolor',[0 1 0], 'markersize',[10]); %creating the projectile
h_proj3=line(0,0,'marker','*','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
h_proj4=line(0,0,'marker','*','color',[0 0 1],'markerfacecolor',[0 0 1], 'markersize',[10]); %creating the projectile
h_proj5=line(0,0,'marker','*','color',[1 0 1],'markerfacecolor',[1 0 1], 'markersize',[10]); %creating the projectile
h_proj6=line(0,0,'marker','*','color',[0 1 1],'markerfacecolor',[0 1 1], 'markersize',[10]); %creating the projectile
drawnow;                                                          %Drawing the ball now


%------------bounce 0-----------------
for t=0:.03:1000;                     %loop for drawing the throw
  %---fw1----
  x1=v01*cos(fi1)*t;                     %calculating x value
  y1=(v01*sin(fi1)*t-.5*g*t^2);            %calculating y value
  set(h_proj1,'xdata',x1,'ydata',y1);    %setting projectile there
  line([x01 x1],[y01 y1],'color',[1 0 0]);%drawing trail of projectile
  x01=x1;                               %setting the values for next line draw
  y01=y1;                               %setting the values for next line draw  
    
  %---fw2----
  x2=v02*cos(fi2)*t;                     %calculating x value
  y2=(v02*sin(fi2)*t-.5*g*t^2);            %calculating y value
  z2=z2+.3;
  set(h_proj2,'xdata',x2,'ydata',y2,'zdata',z2);    %setting projectile there
  line([x02 x2],[y02 y2],[z02 z2],'color',[0 1 0]);%drawing trail of projectile
  x02=x2;                               %setting the values for next line draw
  y02=y2;                               %setting the values for next line draw 
  z02=z2;                               %setting the values for next line draw 
    
  %---fw3----
  x3=v03*cos(fi3)*t;                     %calculating x value
  y3=(v03*sin(fi3)*t-.5*g*t^2);            %calculating y value
  z3=z3-.1;
  set(h_proj3,'xdata',x3,'ydata',y3,'zdata',z3);    %setting projectile there
  line([x03 x3],[y03 y3],[z03 z3],'color',[1 0 0]);%drawing trail of projectile
  x03=x3;                               %setting the values for next line draw
  y03=y3;                               %setting the values for next line draw 
 z03=z3; 
    
  %---fw4----
  x4=v04*cos(fi4)*t;                     %calculating x value
  y4=(v04*sin(fi4)*t-.5*g*t^2);            %calculating y value
  z4=z4-.2;
  set(h_proj4,'xdata',x4,'ydata',y4,'zdata',z4);    %setting projectile there
  line([x04 x4],[y04 y4],[z04 z4],'color',[0 0 1]);%drawing trail of projectile
  x04=x4;                               %setting the values for next line draw
  y04=y4;                               %setting the values for next line draw 
 z04=z4; 
    
  %---fw5----
  x5=v05*cos(fi5)*t;                     %calculating x value
  y5=(v05*sin(fi5)*t-.5*g*t^2);            %calculating y value
  z5=z5-.3;
  set(h_proj5,'xdata',x5,'ydata',y5,'zdata',z5);    %setting projectile there
  line([x05 x5],[y05 y5],[z05 z5],'color',[1 0 1]);%drawing trail of projectile
  x05=x5;                               %setting the values for next line draw
  y05=y5;                               %setting the values for next line draw  
  z05=z5;
    
  %---fw6----
  x6=v06*cos(fi6)*t;                     %calculating x value
  y6=(v06*sin(fi6)*t-.5*g*t^2);            %calculating y value
  z6=z6+.1;
  set(h_proj6,'xdata',x6,'ydata',y6,'zdata',z6);    %setting projectile there
  line([x06 x6],[y06 y6],[z06 z6],'color',[0 1 1]);%drawing trail of projectile
  x06=x6;                               %setting the values for next line draw
  y06=y6;                               %setting the values for next line draw  
  z06=z6;
  
  if y5<0;                               %checking to see if y<0 and loop should be stopped
    drawnow;                            %draw the projectile 
    break;                              %---
  endif;                                %---
  
  drawnow;                              %drawing what the loop created
endfor;