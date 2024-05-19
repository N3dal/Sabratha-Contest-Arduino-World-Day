
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



async function update_monitoring_values(){


    const json_data = await get_data();
    
    if (json_data["BUS-0001"] === null && json_data["BUS-0002"] === null){

    }

    else{
        window.location.reload();
    }


    

}


const interval = setInterval(update_monitoring_values, 250);
