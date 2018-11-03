max_angle = zeros(16,16);

angle_offset = 20; %smallest angle between 2 mounts
h = 200;
%l_crank = 140;
%l_rocker = sqrt(h^2 + l_crank^2);
n_segments = 45;
%linewidth = 2;
%x_lim = rb+50;
%y_lim = rb+50;

Tx=0;
Ty=0;
Tz=0;
%alpha=45/n_segments;
beta=0/n_segments;
gamma=0;

T = ones(7,3);
top = ones(7,3);
base = ones(7,3);
R = eye(3);
lengths = ones(6,n_segments);
servo_angle = zeros(6,n_segments);
B = ones(n_segments, 6); %crank angle?

alpha = 1; %increment by 1 degree)
%rotation matrix
R_x = [1,0,0 ; 0, cos(deg2rad(alpha)), sin(deg2rad(alpha)); 0, -sin(deg2rad(alpha)), cos(deg2rad(alpha))];
R_y = [ cos(deg2rad(beta)),0, -sin(deg2rad(beta)); 0,1,0 ; sin(deg2rad(beta)),0, cos(deg2rad(beta))];
R_z = [cos(deg2rad(gamma)), sin(deg2rad(gamma)), 0; -sin(deg2rad(gamma)), cos(deg2rad(gamma)),0; 0,0,1];
R = R_x * R_y * R_z ;
%translation matrix
T(:,1)=Tx;
T(:,2)=Ty;
T(:,3)=Tz;


rb = 0; %radius of base mm
for loop_rb = 1:15

rb = rb+25;
max_angle(loop_rb+1,1) = rb; %rows show rb starting at 2

%base platform
for i=0:6
    if mod(i,2)==0 %if i is even
    angle = i*60 + angle_offset;  
      
    else
    angle = i*60 - angle_offset;  
    end
    base(i+1,:) = [rb*cos(deg2rad(angle)), rb*sin(deg2rad(angle)), -h];
  B(i+1) = deg2rad(angle+90);
end
%plot base
%plot3(base(:,1),base(:,2),base(:,3),'r', 'linewidth', linewidth); %connects the dots
%hold off;

l_crank = 0;
for loop_crank = 1:15
    
%reset variabes
l_crank = l_crank + 10;
l_rocker = sqrt(h^2 + l_crank^2);
B = ones(n_segments, 6); %crank angle?
lengths = ones(6,n_segments);
servo_angle = zeros(6,n_segments);

max_angle(1,loop_crank+1) = l_crank; %columns show l_crank starting at 2

if l_crank > rb
    continue
end

%reset top platform
for i=0:6
    if mod(i,2)==0 %if i is even
    angle = i*60 + angle_offset;  
      
    else
    angle = i*60 - angle_offset;  
    end
  top(i+1,:) = [rb*cos(deg2rad(angle)), rb*sin(deg2rad(angle)), 0];
end
%plot top
%plot3(top(:,1),top(:,2),top(:,3),'g', 'linewidth', linewidth);
%hold on;

%%{
%move platform
for j = 1:45 %increment degrees
  
%pause(0.0001);
%plot base
%plot3(base(:,1),base(:,2),base(:,3),'r', 'linewidth', linewidth); %connects the dots
%hold on;

%update top mount pts
top = R*transpose(top);
top = transpose(top)+T;

%plot top
%plot3(top(:,1),top(:,2),top(:,3),'g', 'linewidth', linewidth);
%hold on;

%plots links
for i=1:6
lengths(i) = norm(top(i,:) - base(i,:));
M = 2*l_crank*(top(i,3)-base(i,3));
N = 2*l_crank*(cos(B(i))*(top(i,1)-base(i,1)) + sin(B(i))*(top(i,2)-base(i,2)));
L=lengths(i)^2-(l_rocker^2-l_crank^2);
servo_angle(i,j+1) = asin(L/sqrt(M^2+N^2)) - atan(N/M);
crank = [base(i,1) + l_crank*cos(B(i))*cos(servo_angle(i,j+1)), base(i,2) + l_crank*cos(servo_angle(i,j+1))*sin(B(i)),...
        base(i,3) + l_crank*sin(servo_angle(i,j+1))];

link1 = [top(i,:); crank];
link2 = [crank;base(i,:)];
%plot3(link1(:,1),link1(:,2),link1(:,3),'m', 'linewidth', linewidth);
%hold on;
%plot3(link2(:,1),link2(:,2),link2(:,3),'c', 'linewidth', linewidth);
%hold on;

% compute misalignemnt angles
N = cross([base(i,1) base(i,2) 0] - base(1,:), [base(i,1) base(i,2) 0] - crank);
%// angle between plane and line, equals pi/2 - angle between D-E and N
plane_angle(i,j+1) = rad2deg(abs( pi/2 - acos( dot(crank-top(i,:), N)/norm(N)/norm(crank-top(i,:)) ) ));

end

    if isreal(servo_angle)==0
        break
    end

end
%%}

max_angle(loop_rb +1,loop_crank +1) = j;

end



end

surf(max_angle(1,2:15),max_angle(2:15,1),max_angle(2:15,2:15)) %3D plot
xlabel('l_crank');
ylabel('rb');

