var lat = 34.0703625;
var long = -118.4490956;   // Default geocordinates set to Pauley Pavilion 

function success(pos) {   //call back for getCurrentPosition, will change lat and long if successful 
  lat = pos.coords.latitude;
  long = pos.coords.longitude;
}



navigator.geolocation.getCurrentPosition(success)




 function initMap()  //renders actual map
 {
    map = new google.maps.Map(document.getElementById('map'), 
    {
        center: new google.maps.LatLng(lat, long),
        zoom: 14
    });
      }
