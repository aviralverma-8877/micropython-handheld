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
}