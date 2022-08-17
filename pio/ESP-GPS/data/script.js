var Socket = null
function init_socket()
{
    Socket = new WebSocket('ws://'+window.location.hostname+"/ws")
    Socket.onmessage = function(event){
        try
        {
            json = JSON.parse(event.data);
            if(json.action == "alert")
            {
                alert(json.msg)
            }
            if(json.action == "gps_data")
            {
                gps_data = json.value;
                document.getElementById("gps_lat").innerHTML=gps_data.la
                document.getElementById("gps_lng").innerHTML=gps_data.ln
                
                gps_link = "https://maps.google.com/?q="+gps_data.la+","+gps_data.ln
                document.getElementById("gps_link").innerHTML=gps_link
                document.getElementById("gps_link").href = gps_link

                gps_time = gps_data.h + ":" + gps_data.mi + ":" + gps_data.s
                document.getElementById("gps_time").innerHTML=gps_time
                
                gps_date = gps_data.d + "/" + gps_data.m + "/" + gps_data.y
                document.getElementById("gps_date").innerHTML=gps_date
            }
        }
        catch(err)
        {
           console.log("Error : "+err);
        }
    }
    Socket.onopen = function(event){
        console.log("Connected to web sockets...")
    }
    Socket.onclose = function(event){
        console.log("Connection to websockets closed....")
        setTimeout(function(){
            console.log("Reconnecting....")
            init_socket();
        },1000);
    }
    Socket.onerror = function(event){
        console.log("Error in websockets");
    }
}

function send(data)
{
    if(Socket != null)
        Socket.send(data)
}

function send_wifi_cred(ssid, psk)
{
    send(JSON.stringify({"action":"wifi_update","ssid":wifi_ssid.value,"psk":wifi_psk.value}))
    alert("WiFi updated")
}