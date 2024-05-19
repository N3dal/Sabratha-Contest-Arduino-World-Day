
const WARNING_BACKGROUND_COLOR = "#F37F7F";
const CONTAINER_BACKGROUND_COLOR = "#F8F8F8";
const FLASK_SERVER_IP = document.getElementById("flask_server_ip_address").value;
const YES = "Yes";
const NO = "No";
const ON = "On";
const OFF = "Off";
const ACTIVE = "Active";
const DEACTIVATE = "Deactivate";
// id="monitoring-container-repo-2"

async function get_data(){
    console.log(FLASK_SERVER_IP);
    // const response = await fetch("http://192.168.0.12:8080/get_data");
    const response = await fetch("http://"+ FLASK_SERVER_IP + ":8080/get_data");
    const data = await response.json();

    return data;
}

function change_container_background_color(container_id){
    let current_color = document.getElementById(container_id).style.backgroundColor;

    if (current_color == CONTAINER_BACKGROUND_COLOR){
        document.getElementById(container_id).style.backgroundColor = WARNING_BACKGROUND_COLOR; 
    
    }else{
        document.getElementById(container_id).style.backgroundColor = CONTAINER_BACKGROUND_COLOR; 
    }
}

async function update_monitoring_values(){


    const json_data = await get_data();

    // if (json_data["BUS-0001"] != null){
    //     var bus_1_motor_speed = parseInt(json_data["BUS-0001"]["motor-speed-level"])
    //     document.getElementById("bus-1-main-indicator-speed-value").innerHTML = "Speed: " + bus_1_motor_speed.toString() + "%";
    //     document.getElementById("bus-1-motor-speed-gauge-digital-value").innerHTML = bus_1_motor_speed.toString();

    //     document.getElementById("bus-1-sub-status-box-indicator-engine-value").innerHTML = (json_data["BUS-0001"]["engine-state"] == 1) ? ON : OFF;
    //     document.getElementById("bus-1-status-box-indicator-children-left-collision-value").innerHTML = "Collision: " + (json_data["BUS-0001"]["collision-state"]==1 ? YES: NO);
    //     document.getElementById("bus-1-status-box-indicator-children-left-flip-value").innerHTML = "Flip:" + (json_data["BUS-0001"]["tilt-state"]==1 ? YES: NO);

        
    //     const normalized = (bus_1_motor_speed - 0) / (100 - 0);
    //     var bus_1_motor_speed_degree =  -90 + normalized * (90 - -90);
    //     document.getElementById("bus-1-gauge-needle").style.transform = `rotate(${bus_1_motor_speed_degree}deg)`;
    //     document.getElementById("bus-1-gauge-progress-bar").style.transform = `rotate(${bus_1_motor_speed_degree}deg)`;
        
    //     document.getElementById("bus-1-sub-status-box-system-indicator-value").innerHTML = ACTIVE;

    //     var bus_1_img_tag = document.getElementById("bus-1-seat-belt-image");
    //     if (json_data["BUS-0001"]["seat-belt-state"] == 1){
    //         bus_1_img_tag.src = "/static/assets/seat_belt_closed.png";
    //     }else{
    //         bus_1_img_tag.src = "/static/assets/seat_belt_open.png";
    //     }


    //     // console.log(json_data["bus-0001"]["tilt-state"]);

    // }
    // else{
    //     document.getElementById("bus-1-sub-status-box-system-indicator-value").innerHTML = DEACTIVATE;
    // }

    // if (json_data["BUS-0002"] != null){
    //     var bus_1_motor_speed = parseInt(json_data["BUS-0002"]["motor-speed-level"])
    //     document.getElementById("bus-2-main-indicator-speed-value").innerHTML = "Speed: " + bus_1_motor_speed.toString() + "%";
    //     document.getElementById("bus-2-motor-speed-gauge-digital-value").innerHTML = bus_1_motor_speed.toString();

    //     document.getElementById("bus-2-sub-status-box-indicator-engine-value").innerHTML = (json_data["BUS-0002"]["engine-state"] == 1) ? ON : OFF;
    //     document.getElementById("bus-2-status-box-indicator-children-left-collision-value").innerHTML = "Collision: " + (json_data["BUS-0002"]["collision-state"]==1 ? YES: NO);
    //     document.getElementById("bus-2-status-box-indicator-children-left-flip-value").innerHTML = "Flip:" + (json_data["BUS-0002"]["tilt-state"]==1 ? YES: NO);

        
    //     const normalized = (bus_1_motor_speed - 0) / (100 - 0);
    //     var bus_1_motor_speed_degree =  -90 + normalized * (90 - -90);
    //     document.getElementById("bus-2-gauge-needle").style.transform = `rotate(${bus_1_motor_speed_degree}deg)`;
    //     document.getElementById("bus-2-gauge-progress-bar").style.transform = `rotate(${bus_1_motor_speed_degree}deg)`;
        
    //     document.getElementById("bus-2-sub-status-box-system-indicator-value").innerHTML = ACTIVE;

    //     var bus_1_img_tag = document.getElementById("bus-2-seat-belt-image");
    //     if (json_data["BUS-0002"]["seat-belt-state"] == 1){
    //         bus_1_img_tag.src = "/static/assets/seat_belt_closed.png";
    //     }else{
    //         bus_1_img_tag.src = "/static/assets/seat_belt_open.png";
    //     }


        // console.log(json_data["bus-0001"]["tilt-state"]);

    // }
    // else{
    //     document.getElementById("bus-2-sub-status-box-system-indicator-value").innerHTML = DEACTIVATE;
    // }



}


const interval = setInterval(update_monitoring_values, 500);
