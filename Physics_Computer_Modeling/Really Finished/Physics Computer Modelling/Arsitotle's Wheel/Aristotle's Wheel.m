%bullshit program solving a non paradox

%-------dialog box asking user for radius-----------
input = inputdlg ({"Radius"},"Cycloid",[1,20],{"1"});   %getting user imput
Ru=str2double(input{1});                                %radius converted from user input

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Aristotle's Wheel");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Aristotle's Wheel, R=" num2str(Ru) ];                                   %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("Y",'fontsize',[17]);                                               %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                               %labeling x axis
axis('equal',[-2 4*pi+2 -Ru Ru+2]);                                             %setting axis limits
grid on;                                                                        %toggleling the grid in coordinate system
drawnow;                                                                        %drawing it now

%===Drawing the Wheel===
X_wheel=0;      %setting initial values
Y_wheel=0;      %setting initial values
R=1;            %setting initial values
k=1;            %setting initial values
for fi=0:.01:2*pi;         %this calculates the points of the circle that will be used a the wheel
X_wheel(k)=R*cos(fi);
Y_wheel(k)=R+R*sin(fi);
k=k+1;
endfor;
h_wheel=line(X_wheel,Y_wheel,'linewidth',[5]);  %this line draws the wheel from the calculated data

X_R1=0;   %setting initial values
Y_R1=0;   %setting initial values
h_rad=line(0,0,'marker','o'); %initializing the line that represents the radius of the wheel
w=1;    %setting initial values for agualar velocity
v=w*R;    %setting initial values for velocity
R1=R;   %setting initial values
x0=R;   %setting initial values
y0=1;   %setting initial values
xu0=Ru;   %setting initial values
yu0=1;    %setting initial values

for t=0:.04:4*pi;   %loop that runs for two rotations of the wheel, t represents time
  set(h_wheel,'xdata',X_wheel+v*t,'ydata',Y_wheel); %setting the wheel to a place
  
  %setting the coordinates that are used to draw the standard radius and its trail in relation to the passing time
  x=R1*cos(-w*t);
  y=R+R1*sin(-w*t);
  X_rad=[v*t, v*t+x]; 
  Y_rad=[R, y];
  X_R1=[v*t+x];
  Y_R1=[y];
  
  %setting the coordinates that are used to draw the user provided radius and its trail in relation to the passing time
  xu=Ru*cos(-w*t);
  yu=R+Ru*sin(-w*t);
  Xu_rad=[v*t, v*t+xu];
  Yu_rad=[R, yu];
  Xu_R1=[v*t+xu];
  Yu_R1=[yu];
  set(h_rad,'xdata',Xu_rad,'ydata',Yu_rad);   %setting the radius to a specific place
  
  line([x0 X_R1],[y0 Y_R1],'color',[0 0 1]);      %drawing line of r=1
  line([xu0 Xu_R1],[yu0 Yu_R1],'color',[1 0 0]);  %drawing line of user input
  
  %===storing variable for use in the next drawing of the lines
  x0=X_R1;
  y0=Y_R1;
  xu0=Xu_R1;
  yu0=Yu_R1;
  drawnow;    %drawing the things now
endfor;