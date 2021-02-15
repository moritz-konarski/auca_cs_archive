%bullshit program solving a non paradox

%-------dialog bos asking user for amplitude-----------
input = inputdlg ({"Radius"},...
"Cycloid",[1,20],{"1"});   %getting user imput
Ru=str2double(input{1});                                     %amplitude converted from user input

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Aristotle's Wheel");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Aristotle's Wheel, R=" num2str(Ru) ];                                                    %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("Y",'fontsize',[17]);                                              %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                               %labeling x axis
axis('equal',[-Ru-2 4*pi+2+Ru -Ru Ru+2]);
line([-Ru-2 4*pi+2+Ru],[0 0],'linewidth',[2.5]);
grid on;                                                                        %toggleling the grid in coordinate system
drawnow;                                                                        %drawing it now

X_wheel=0;
Y_wheel=0;
R=1;
k=1;

for fi=0:.02:2*pi;          %Drawing the Wheel
X_wheel(k)=R*cos(fi);
Y_wheel(k)=R+R*sin(fi);
k=k+1;
endfor;

X_R1=0;
Y_R1=0;
h_wheel=line(X_wheel,Y_wheel,'linewidth',[5]);
h_rad=line(0,0,'marker','o');
w=1;
v=w*R;
R1=R;
x0=R;
y0=1;
xu0=Ru;
yu0=1;

for t=0:.02:4*pi;
  set(h_wheel,'xdata',X_wheel+v*t,'ydata',Y_wheel);
  x=R1*cos(-w*t);
  y=R+R1*sin(-w*t);
  X_rad=[v*t, v*t+x];
  Y_rad=[R, y];
  X_R1=[v*t+x];
  Y_R1=[y];
  
  xu=Ru*cos(-w*t);
  yu=R+Ru*sin(-w*t);
  Xu_rad=[v*t, v*t+xu];
  Yu_rad=[R, yu];
  Xu_R1=[v*t+xu];
  Yu_R1=[yu];
  %set(h_rad,'xdata',X_rad,'ydata',Y_rad);
  set(h_rad,'xdata',Xu_rad,'ydata',Yu_rad);
  
  line([x0 X_R1],[y0 Y_R1],'color',[0 0 1]);
  line([xu0 Xu_R1],[yu0 Yu_R1],'color',[1 0 0]);
  
  x0=X_R1;
  y0=Y_R1;
  xu0=Xu_R1;
  yu0=Yu_R1;
  drawnow;
endfor;














