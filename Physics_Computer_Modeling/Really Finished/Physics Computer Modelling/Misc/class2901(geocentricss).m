%class 2401
%home 29.01.
%solar system (geocentric)

%------------preparation-----------------------------------------------------------------------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Solar System"); %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1], 'xlim',[-17 17],'ylim',[-17 17]);  %Creating Axis
grid on;                                        %turing on grid in coordinate system
xlabel ("X-Axis");                               %labeling the axis
ylabel ("Y-Axis");                               %labeling the axis
zlabel ("Z-Axis");                               %labeling the axis
axis ('square');                                 %squaring axis
%view(325,135)                                   %Tilting coordinate system

%------------Drawing Sun------------------------------------------------------------------------------------------
h_Sun=line(0,0,0,'marker','o','markersize',[15],'markerfacecolor','yellow','color','yellow'); %creating the ball
we=1;               %angular speed earth
re=5;               %orbit radius earthxs=ys=0;            

%------------Drawing Mercure----------------------------------------------------------------------------------------
h_Mercure=line(0,0,0,'marker','o','markersize',[5],'color',[.7 0 0],'markerfacecolor',[.7 0 0]); %creating the ball
wm=3;               %angular speed mercure
rm=3;               %orbit radius mecure

%------------Drawing Venus----------------------------------------------------------------------------------------
h_Venus=line(0,0,0,'marker','o','markersize',[6],'color',[0 .7 0],'markerfacecolor',[0 .7 0]); %creating the ball
wv=1.5;             %angular speed venus
rv=4;               %orbit radius venus

%------------Drawing Earth----------------------------------------------------------------------------------------
h_Earth=line(0,0,0,'marker','o','markersize',[8],'color',[0 0 1],'markerfacecolor',[0 0 1]); %creating the ball
xe=ye=0;

%------------Drawing Moon------------------------------------------------------------------------------------------
h_Moon=line(0,0,0,'marker','o','markersize',[3],'color',[.3 .3 .3],'markerfacecolor',[.3 .3 .3]); %creating the ball
wmo=12;             %angular speed Moon
rmo=.7;             %orbit radius moon

%------------Drawing Mars------------------------------------------------------------------------------------------
h_Mars=line(0,0,0,'marker','o','markersize',[7],'color',[1 0 0],'markerfacecolor',[1 0 0]); %creating the ball
wma=.8;             %angular speed Mars
rma=7;              %orbit radius Mars

%------------Drawing Marsmoom------------------------------------------------------------------------------------------
h_Marsmoon=line(0,0,0,'marker','o','markersize',[2.5],'color',[0 0 0],'markerfacecolor',[0 0 0]); %creating the ball
wmma=10;             %angular speed Marsmoon
rmma=.5;             %orbit radius Marsmoon

%------------Drawing Jupiter------------------------------------------------------------------------------------------
h_Jupiter=line(0,0,'marker','o','markersize',[12],'color',[1 .5 .3],'markerfacecolor',[1 .5 .3]);
wj=.5;              %angular speed jupiter
rj=11;              %orbit radius jupiter

%------------Drawing MoonJ1------------------------------------------------------------------------------------------
h_MoonJ1=line(0,0,'marker','o','markersize',[3],'color',[.3 .3 .3],'markerfacecolor',[.3 .3 .3]);
wmj1=10;             %angular speed Moon
rmj1=.6;             %orbit radius moon

%------------Drawing MoonJ2------------------------------------------------------------------------------------------
h_MoonJ2=line(0,0,'marker','o','markersize',[3],'color',[0 .3 .3],'markerfacecolor',[0 .3 .3]);
wmj2=13;             %angular speed Moon
rmj2=1;             %orbit radius moon

%------------Drawing MoonJ3------------------------------------------------------------------------------------------
h_MoonJ3=line(0,0,'marker','o','markersize',[3],'color',[.3 0 .3],'markerfacecolor',[.3 0 .3]);
wmj3=12;             %angular speed Moon
rmj3=.9;             %orbit radius moon

%------------Drawing MoonJ4------------------------------------------------------------------------------------------
h_MoonJ4=line(0,0,'marker','o','markersize',[3],'color',[.3 0 .6],'markerfacecolor',[.3 0 .6]);
wmj4=9;             %angular speed Moon
rmj4=1.2;             %orbit radius moon
      
%------------Making planets move------------------------------------------------------------------------------------

%---Sun---
%set(h_Sun,'xdata',xs,'ydata',ys);

for t=0:.02:4*pi                                     %setting up loop for one rotation
   
  %----Earth----
  xe=re*cos(we*t);                                   %getting x for earth
  ye=re*sin(we*t);                                   %getting y for earth
  set(h_Earth,'xdata',0,'ydata',0);                %putting earth there
   
  %----Moon----
  xmo=rmo*cos(wmo*t);                                %getting x for moon
  ymo=rmo*sin(wmo*t);                                %getting y for moon
  set(h_Moon,'xdata',xmo,'ydata',ymo);         %putting moon there
  
  %----Mercure----
  xm=rm*cos(wm*t);                                   %getting x for mercure
  ym=rm*sin(wm*t);                                   %getting y for mercure
  set(h_Mercure,'xdata',xm-xe,'ydata',ym-ye);              %putting mercure there
  
  %----Venus----
  xv=rv*cos(wv*t);                                   %getting x for venus
  yv=rv*sin(wv*t);                                   %getting y for venus
  set(h_Venus,'xdata',xv-xe,'ydata',yv-ye);                %putting venus there
 
  %----Sun----
  xs=xe;
  ys=ye;
  set(h_Sun,'xdata',xs,'ydata',ys);
  
  %----Mars----
  xma=rma*cos(wma*t);                                %getting x for mars
  yma=rma*sin(wma*t);                                %getting y for mars
  set(h_Mars,'xdata',xma-xe,'ydata',yma-ye);               %putting mars there
  
  %----Marsmoon----
  xmma=rmma*cos(wmma*t);                                %getting x for mars
  ymma=rmma*sin(wmma*t);                                %getting y for mars
  set(h_Marsmoon,'xdata',xma+xmma-xe,'ydata',yma+ymma-ye);    %putting mars there
  
  %----Jupiter----
  xj=rj*cos(wj*t)-xe;                                   %getting x for jupiter
  yj=rj*sin(wj*t)-ye;                                   %getting y for jupiter
  set(h_Jupiter,'xdata',xj,'ydata',yj);              %putting jupiter there
  
  %----MoonJ1----
  xmj1=rmj1*cos(wmj1*t);                                %getting x for earth
  ymj1=rmj1*sin(wmj1*t);                                %getting y for earth
  set(h_MoonJ1,'xdata',xj+xmj1,'ydata',yj+ymj1);         %putting earth there
  
  %----MoonJ2----
  xmj2=rmj2*cos(wmj2*t);                                %getting x for earth
  ymj2=rmj2*sin(wmj2*t);                                %getting y for earth
  set(h_MoonJ2,'xdata',xj+xmj2,'ydata',yj+ymj2);         %putting earth there
  
  %----MoonJ3----
  xmj3=rmj3*cos(wmj3*t);                                %getting x for earth
  ymj3=rmj3*sin(wmj3*t);                                %getting y for earth
  set(h_MoonJ3,'xdata',xj+xmj3,'ydata',yj+ymj3);         %putting earth there
  
  %----MoonJ4----
  xmj4=rmj4*cos(wmj4*t);                                %getting x for earth
  ymj4=rmj4*sin(wmj4*t);                                %getting y for earth
  set(h_MoonJ4,'xdata',xj+xmj4,'ydata',yj+ymj4);         %putting earth there
  
  drawnow;
endfor