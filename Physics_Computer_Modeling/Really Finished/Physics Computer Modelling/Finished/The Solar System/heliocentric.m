%Heliocentric

%------------preparation-----------------------------------------------------------------------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Heliocentric"); %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1], 'xlim',[-13 13],'ylim',[-13 13]);  %Creating Axis
grid off;                                        %turing on grid in coordinate system
xlabel ("X-Axis");                               %labeling the axis
ylabel ("Y-Axis");                               %labeling the axis
zlabel ("Z-Axis");                               %labeling the axis
axis ('square');                                 %squaring axis
drawnow

%----------------Changeable Variables-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------------------------------------------
n=1;              %Number of Revolutions of earth/number of years shown
i=.05;            %Interval during for-loop
g=0;              %Set to >1 to deactivate lines of planets

%---------------pre-calculations----------------------------------------------------------------------------------
l=n.*2.*pi;     %limit for for-loop

%----------------Preparing the Planets----------------------------------------------------------------------------
%------------w[x] is the angular speed; r[x] is the radius relative to the sun------------------------------------
%----To adapt this system to center around other planets, set ws and rs for the sun to the ones of the desired planet
%------------Drawing Sun------------------------------------------------------------------------------------------
h_Sun=line(0,0,0,'marker','o','markersize',[17],'markerfacecolor','yellow','color','yellow'); %creating the ball
ws=0;               %angular speed
rs=0;               %orbit radius

%------------Drawing Mercure----------------------------------------------------------------------------------------
h_Mercure=line(0,0,0,'marker','o','markersize',[7],'color',[.7 0 0],'markerfacecolor',[.7 0 0]); %creating the ball
wm=2;               %angular speed mercure
rm=3;               %orbit radius mecure

%------------Drawing Venus----------------------------------------------------------------------------------------
h_Venus=line(0,0,0,'marker','o','markersize',[10],'color',[0 .7 0],'markerfacecolor',[0 .7 0]); %creating the ball
wv=1.5;             %angular speed venus
rv=4;               %orbit radius venus

%------------Drawing Earth----------------------------------------------------------------------------------------
h_Earth=line(0,0,0,'marker','o','markersize',[10],'color',[0 0 1],'markerfacecolor',[0 0 1]); %creating the ball
we=1;               %angular speed earth
re=5;               %orbit radius earth

%------------Drawing Moon------------------------------------------------------------------------------------------
h_Moon=line(0,0,0,'marker','o','markersize',[5],'color',[.3 .3 .3],'markerfacecolor',[.3 .3 .3]); %creating the ball
wem=12;             %angular speed Moon
rem=.7;             %orbit radius moon

%------------Drawing Mars------------------------------------------------------------------------------------------
h_Mars=line(0,0,0,'marker','o','markersize',[9],'color',[1 0 0],'markerfacecolor',[1 0 0]); %creating the ball
wma=.8;             %angular speed Mars
rma=7;              %orbit radius Mars

%------------Drawing Marsmoom------------------------------------------------------------------------------------------
h_Marsmoon=line(0,0,0,'marker','o','markersize',[4.5],'color',[0 0 0],'markerfacecolor',[0 0 0]); %creating the ball
wmam=10;             %angular speed Marsmoon
rmam=.5;             %orbit radius Marsmoon

%------------Drawing Jupiter------------------------------------------------------------------------------------------
h_Jupiter=line(0,0,'marker','o','markersize',[14],'color',[1 .5 .3],'markerfacecolor',[1 .5 .3]);
wj=.5;              %angular speed jupiter
rj=11;              %orbit radius jupiter

%------------Drawing MoonJ1------------------------------------------------------------------------------------------
h_MoonJ1=line(0,0,'marker','o','markersize',[5],'color',[.3 .3 .3],'markerfacecolor',[.3 .3 .3]);
wmj1=10;             %angular speed Moon
rmj1=.6;             %orbit radius moon

%------------Drawing MoonJ2------------------------------------------------------------------------------------------
h_MoonJ2=line(0,0,'marker','o','markersize',[5],'color',[0 .3 .3],'markerfacecolor',[0 .3 .3]);
wmj2=13;             %angular speed Moon
rmj2=1;               %orbit radius moon

%------------Drawing MoonJ3------------------------------------------------------------------------------------------
h_MoonJ3=line(0,0,'marker','o','markersize',[5],'color',[.3 0 .3],'markerfacecolor',[.3 0 .3]);
wmj3=12;             %angular speed Moon
rmj3=.9;             %orbit radius moon

%------------Drawing MoonJ4------------------------------------------------------------------------------------------
h_MoonJ4=line(0,0,'marker','o','markersize',[5],'color',[.3 0 .6],'markerfacecolor',[.3 0 .6]);
wmj4=9;               %angular speed Moon
rmj4=1.2;             %orbit radius moon
 
drawnow
%------------Making planets move------------------------------------------------------------------------------------
%-------------------------------------------------------------------------------------------------------------------
for t=0:i:l                                          %setting up loop for one rotation
  
  %----Sun----
  xs=rs*cos(ws*t);                                   %getting x for sun
  ys=rs*sin(ws*t);                                   %getting y for sun
  set(h_Sun,'xdata',xs,'ydata',ys);                  %putting sun there
  
  %----Mercure----
  xm=rm*cos(wm*t);                                   %getting x for mercure
  ym=rm*sin(wm*t);                                   %getting y for mercure
  set(h_Mercure,'xdata',xm-xs,'ydata',ym-ys);              %putting mercure there
  
  %----Venus----
  xv=rv*cos(wv*t);                                   %getting x for venus
  yv=rv*sin(wv*t);                                   %getting y for venus
  set(h_Venus,'xdata',xv-xs,'ydata',yv-ys);                %putting venus there
  
  %----Earth----
  xe=re*cos(we*t);                                   %getting x for earth
  ye=re*sin(we*t);                                   %getting y for earth
  set(h_Earth,'xdata',xe-xs,'ydata',ye-ys);                %putting earth there

  %----Moon----
  xem=rem*cos(wem*t)+xe;                                %getting x for moon
  yem=rem*sin(wem*t)+ye;                                %getting y for moon
  set(h_Moon,'xdata',xem-xs,'ydata',yem-ys);                  %putting moon there
  
  %----Mars----
  xma=rma*cos(wma*t);                                %getting x for mars
  yma=rma*sin(wma*t);                                %getting y for mars
  set(h_Mars,'xdata',xma-xs,'ydata',yma-ys);               %putting mars there
  
  %----Marsmoon----
  xmam=rmam*cos(wmam*t)+xma;                                %getting x for marsmoon
  ymam=rmam*sin(wmam*t)+yma;                                %getting y for marsmoon
  set(h_Marsmoon,'xdata',xmam-xs,'ydata',ymam-ys);                %putting marsmoon there
  
  %----Jupiter----
  xj=rj*cos(wj*t);                                   %getting x for jupiter
  yj=rj*sin(wj*t);                                   %getting y for jupiter
  set(h_Jupiter,'xdata',xj-xs,'ydata',yj-ys);              %putting jupiter there
  
  %----MoonJ1----
  xmj1=rmj1*cos(wmj1*t)+xj;                                %getting x for jupitermoon
  ymj1=rmj1*sin(wmj1*t)+yj;                                %getting y for jupitermoon
  set(h_MoonJ1,'xdata',xmj1-xs,'ydata',ymj1-ys);                 %putting jupitermoon there
  
  %----MoonJ2----
  xmj2=rmj2*cos(wmj2*t)+xj;                                %getting x for jupitermoon
  ymj2=rmj2*sin(wmj2*t)+yj;                                %getting x for jupitermoon
  set(h_MoonJ2,'xdata',xmj2-xs,'ydata',ymj2-ys);                 %putting jupitermoon there
  
  %----MoonJ3----
  xmj3=rmj3*cos(wmj3*t)+xj;                                %getting x for jupitermoon
  ymj3=rmj3*sin(wmj3*t)+yj;                                %getting x for jupitermoon
  set(h_MoonJ3,'xdata',xmj3-xs,'ydata',ymj3-ys);                 %putting jupitermoon there
  
  %----MoonJ4----
  xmj4=rmj4*cos(wmj4*t)+xj;                                %getting x for jupitermoon
  ymj4=rmj4*sin(wmj4*t)+yj;                                %getting x for jupitermoon
  set(h_MoonJ4,'xdata',xmj4-xs,'ydata',ymj4-ys);        %putting jupitermoon there
  
  drawnow;
  
  if (mod(t,0.5.*i)==g)  %Trails of the planets in an interval
    
    line(xs,ys,'marker','.','markersize',[7]);   %Sun
    line(xm-xs,ym-ys,'marker','.','markersize',[7]);   %Mercure
    line(xv-xs,yv-ys,'marker','.','markersize',[7]);   %Venus
    line(xe-xs,ye-ys,'marker','.','markersize',[7]);   %Earth
    line(xma-xs,yma-ys,'marker','.','markersize',[7]);   %Mars
    line(xj-xs,yj-ys,'marker','.','markersize',[9]);   %Jupiter
    
  endif

endfor