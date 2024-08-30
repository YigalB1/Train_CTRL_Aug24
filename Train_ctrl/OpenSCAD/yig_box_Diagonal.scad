use <Screw_holder.scad>;
// use <kcd3_switch.scad>
//use <USB_supply.scad>
use <Volt_Amper_Meter.scad>;
// use <DC_plug_NO_pcb.scad> to replace with another
// not compatible
// new hole: 3.8 diamater

// Box parameters
// yig_diagonal_box(x=100,y=70,front_h=40,back_h=60,width=2,side_x=6,select=1,label="My label",to_print="box")
length= 100;
width = 70;
f_height = 40;
b_height = 60; 
box_width = 2;
side_x = 6; // unused parameter????


pin_negative(size=2,hole_h=hole_l);




module dxf() {
    import ("DXF_PCB_Train_CTRL_2024-08-23.dxf");
} 

//print_cover();
print_box();

module print_cover() {
    difference() {
        union() {
            yig_diagonal_box(to_print="cover");
            translate([70,74,-1.5]) text_it("Power");
            translate([74,66,-1.5]) text_it("ON");
            translate([72,25,-1.5]) text_it("OFF");
            translate([25,66,-1.5]) text_it("VOLT");
            translate([25,25,-1.5]) text_it("AMPER");
        } // of union
        
 //       translate([80,50,0]) rotate([0,0,90]) kcd3_switch();
        translate([40,50,0]) Volt_Amper_Meter();
    } // of difference()
} // of print_cover()

module text_it(t_in="my text") {
    font = "Liberation Sans";
    linear_extrude(height = 2) {
       text(text = t_in, font = font, size = 6);
    }
} // of text_it()

module print_box() {
    usb_vec = [28,30,0];
    usb_y_shift = 6;
    screw_x = 10;
    screw_y = 62;
    screw_h = 0;
   
        
    difference() {
        union() {
            yig_diagonal_box(x=length,y=width,front_h=f_height,back_h=b_height,to_print="box");
//            translate([0,usb_y_shift,1]) translate(usb_vec)
//                usb_power_supply(par="screw_holes");               
        } // of union()
        // holes for the USB connectors
//        translate([0,usb_y_shift,7]) translate(usb_vec)
//            usb_power_supply(par="full_model");
        // holes for DC plugs
        translate([98,20,15]) rotate([0,0,0]) side_dc_connector();
        translate([98,45,15]) rotate([0,0,0]) side_dc_connector();
        translate([98,45,35]) rotate([0,0,0]) side_dc_connector();
        
        
        
        // holes for screws on floor
        translate([screw_x,screw_x,screw_h])    screw_3mm();
        translate([screw_x,screw_y,screw_h])    screw_3mm();
        translate([screw_x+75,screw_x,screw_h]) screw_3mm();
        translate([screw_x+75,screw_y,screw_h]) screw_3mm();
        
    } // of difference
    
    module screw_3mm() {
        d = 3.2 + +0.2;
        translate([0,0,0]) rotate([0,0,0])
            cylinder(d=d,h=10,center=true,$fn=60);
    } // of screw_3mm
    
    module side_dc_connector() {
        cyl_d = 7.7+0.3;
        rotate([0,90,0]) cylinder(d=cyl_d,h=10,center=true,$fn=60);
    } // of side_dc_connector()
    

} // of print_box()



module yig_diagonal_box(x=100,y=70,front_h=40,back_h=60,width=2,side_x=6,select=1,label="My label",to_print="box") {
    angle=atan((back_h-front_h)/y);
    y_cover=(back_h-front_h)/(sin(angle));
    
    base_points = [[0,0],[x,0],[x,y],[0,y]];
    l_r_points = [[0,0],[front_h,0],[back_h,y],[0,y]];
    front_points = [[0,0],[x,0],[x,front_h],[0,front_h]];
    back_points = [[0,0],[x,0],[x,back_h],[0,back_h]];
    cover_points = [[0,0],[x,0],[x,y_cover],[0,y_cover]];
    corner_x=7;    
    
    if (to_print=="box") {
        echo("here 1");
        box_to_print(dummy_pins_="false");
    } // of if()
    else if (to_print=="cover") {
        echo("here 2");
        // inside the difference the cover is aligned to the box
        // the diff before is to bring the result to flat orientation
        translate([0,0,-front_h]) rotate([-angle,0,0]) 
        difference() {
            translate([0,0,front_h]) rotate([angle,0,0]) cover(h=width);
            box_to_print(dummy_pins_="true");
        } // of difference()

    } // of else
    
    
    module box_to_print(dummy_pins_="false") {
        echo(dummy_pins_);
        difference() {
            box(dummy_pins=dummy_pins_);
            translate([0,0,front_h]) rotate([angle,0,0]) cover(h=width+3);    
        } // of difference
        if (dummy_pins_=="true") {
            box(dummy_pins="true");
        } // of if()

    }// of box_to_print()
    
    
    
    module cover(h=width) {
        color("cyan")  linear_extrude(h, center=true)
        polygon(cover_points);        
    } // of cover()
    
    module box(dummy_pins="false"){
        echo(dummy_pins);
        if (dummy_pins=="false") {
            base();
            left_wall();
            right_wall();
            front_wall();
            back_wall();
        } // of if()
        
        // front left
        translate([0,0,0])
            corner(corner_h=front_h,dummy_pins_in=dummy_pins);
        // front right
        translate([x-corner_x,0,0])
            corner(corner_h=front_h,dummy_pins_in=dummy_pins);
        // Back left
        translate([0,y-corner_x,0])
            corner(corner_h=back_h,dummy_pins_in=dummy_pins);
        // Back right 
        translate([x-corner_x,y-corner_x,0])
            corner(corner_h=back_h,dummy_pins_in=dummy_pins);
    } // of box
    
    module base() {
        color("gray")  linear_extrude(width, center=true)
        polygon(base_points);        
    } // of base()
    
    module left_wall() {
        rotate([0,-90,0]) translate([0,0,-width]) 
            linear_extrude(width)
                polygon(l_r_points);   
    } // of left_wall()

   module right_wall() {
        rotate([0,-90,0]) translate([0,0,-x]) 
            linear_extrude(width)
                polygon(l_r_points);
   } // of right_wall()
   
   module front_wall() {
        color("red") rotate([90,0,0]) translate([0,0,-width]) 
            linear_extrude(width) 
                polygon(front_points);
   } // of front_wall()
   
   module back_wall() {
        color("blue") rotate([90,0,0]) translate([0,0,-y]) 
            linear_extrude(width)
                polygon(back_points);
   } // of back_wall()




module corner(corner_h=10,dummy_pins_in="false") {
    
        // dummy_pins_in - to add dummy external pins to make a hole in the cover
    echo(dummy_pins_in);
        //cone_h=6;
        hole_l = 10;
        //m2_insert_d = 3.8-0.2;
        //m3_insert_d = 3.4-0.2;
        //insert_d = m2_insert_d;
        
        if (dummy_pins_in=="true") {
            translate([corner_x/2,corner_x/2,corner_h-6])
                pin_negative(size=2,hole_h=hole_l);            
        } // of if()
        else {              
            difference() {
                cube ([corner_x,corner_x,corner_h], center=false);  
                translate([corner_x/2,corner_x/2,corner_h-hole_l])
                    pin_negative(size=2,hole_h=hole_l);            
            } // of difference()
        } // of else
        
              
           
        module cone() {
            // to make it easy to push the screw holder
            color("red") cylinder(r1=0,r2=2,h=cone_h);
        } // of cone() module        
    } // of corner()
    
} // of yig_diagonal_box
