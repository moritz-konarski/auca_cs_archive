figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Drawing Functions")
bsin = uicontrol ("string", "y=sin(5t)", "position",[10 450 180 40]);
be = uicontrol ("string", "y=e^(-4t^2)", "position",[10 400 180 40]);
bsqrt = uicontrol ("string", "y=1/(sqrt(1-t^2))", "position",[10 350 180 40]);
btan = uicontrol ("string", "y=arctan(t)", "position",[10 300 180 40]);
bfun = uicontrol ("string", "y=3t^2+2t+1", "position",[10 250 180 40]);

function togglebuttonbsin(, 0)
x = 0:0.05:2*pi;
plot (x, sin (5*x));
grid on
xlabel ("t");
ylabel ("sin (5t)");
title ("Sin (5t)");
axis('equal',[-.5 2*pi+.5 -1.1 1.1])
endfunction
%'ButtonPushedFcn', @(btn,event) plotButtonPushed(bin,f1)

bsin = uicontrol ("string", "y=sin(5t)", "position",[10 450 180 40]);
be = uicontrol ("string", "y=e^(-4t^2)", "position",[10 400 180 40]);
bsqrt = uicontrol ("string", "y=1/(sqrt(1-t^2))", "position",[10 350 180 40]);
btan = uicontrol ("string", "y=arctan(t)", "position",[10 300 180 40]);
bfun = uicontrol ("string", "y=3t^2+2t+1", "position",[10 250 180 40]);
