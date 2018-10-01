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



        var currentLocationMarker = new google.maps.Marker({
          position: {lat: lat, lng: long},
          map: map
        });


        var marker = new google.maps.Marker({
        	position: {lat: 34.0626647, lng: -118.4472813},
        	map: map
        });

         var flightPlanCoordinates = [
    {lat: lat, lng: long},
    {lat: 34.0626647, lng: -118.4472813},

  ];

  //  var flightPath = new google.maps.Polyline({
  //   path: flightPlanCoordinates,
  //   geodesic: true,
  //   strokeColor: '#FF0000',
  //   strokeOpacity: 1.0,
  //   strokeWeight: 2
  // });
}


