function bsinp ('object_handle', 'event')
x = 0:0.05:2*pi;
plot (x, sin (5*x));
grid on
xlabel ("t");
ylabel ("sin (5t)");
title ("Sin (5t)");
axis('equal',[-.5 2*pi+.5 -1.1 1.1])
endfunction