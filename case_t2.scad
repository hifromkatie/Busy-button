module bottom_case(){
    difference(){
        union(){
            translate([2,2,2]) cube([56,56,12]);
            base();
        }
        
        translate([14,4,2]) bottom_space();      
    }
}
module bottom_space(){
    union(){
        batt_space();
        translate([-10,14,8])board_space();
    }
}
module board_space(){
    union(){
        cube([51, 24,15]);
        translate([7, 15, 1.4])cube([8,15,16]);
        translate([-5,7,0])cube([10,10,8]); //add charging hole
    }
    
}
module batt_space(){
    cube([32,40,16]);
    translate([0,39,2])cube([32,13,16]);
}
module base(){
    cube([60,60,2]);
}

module top(){
    difference(){
        cube([60,60,60]);
        union(){
            translate([5,5,-1])cube([50,50,56]);
            translate([2,2,-1])cube([56,56,13]);
            translate([21,30,55])cylinder(h=20, r=4, center=true);
            translate([39,30,55])cylinder(h=20, r=6, center=true);
        }
        translate ([55,25,-1])cube([10,10,17]); //add charging hole
    }
}


translate([80,0,0])bottom_case();
translate([0,0,2])top();