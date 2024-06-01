String webtrangTrai = R"***(
<!DOCTYPE html>
<html lang="en">
<head>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script src="https://code.highcharts.com/highcharts.js"></script>

    <title>He thong giam sat trang trai </title>
    <style>
      body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            margin: 0;
            padding: 0;
        }

      header {
            background-color: #a0db8e;
            color: #fff;
            text-align: center;
            padding: 10px;
            text-shadow: 0 0 5px blue;
            margin-bottom: 20px;
        }

      h1 {
            margin-top: 20px;
        }

      .data {
            display: flex;
            flex-wrap: wrap;
            justify-content: space-around;
            background-color: #f0f0f0;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 20px;
        }

      .data_child {
            width: 300px;
            background-color: #fff;
            border: 1px solid #ccc;
            padding: 15px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            margin: 10px;
            box-sizing: border-box;
        }
         
     
      .toggle-switch-container {
            display: flex;
            align-items: center;
            justify-content: space-between;
            padding:10px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(190, 140, 140, 0.1);
        }

     
      .data_child h2 {
            color: #333;
        }

      .data_child p {
            color: #666;
        }

      #iconTT img {
            max-width: 50px;
        }

      .data_child:hover {
            transform: scale(1.05);
            transition: transform 0.3s ease-in-out;
        }


      .sensor-data,
      .load-sensor-data,
      .toggle-container {
            border: 1px solid #a0db8e;
            text-align: center;
            background-color: #fff;
            box-shadow: 0 0 5px rgba(0, 0, 0, 0.2);
            border-radius: 15%;
            padding: 20px;
            margin-bottom: 20px;
            width : 300px;
            height : 400px;
            float: left;
            text-align: center;
        }

      footer {
            background-color: #ffc3a0;
            color: #fff;
            text-align: center;
            width: 100%;
            text-shadow: 0 0 5px rgb(20, 24, 21);
            padding: 10px 0;
            position: fixed;
            bottom: 0;
        }

      .fa-database {
            color: rgb(20, 54, 113);
        }

      .fa-carrot {
            color: rgb(255, 89, 0);
        }

      .fa-tint {
            color: rgb(0, 149, 255);
        }

      .fa-thermometer-half {
            color: rgb(255, 0, 76)
        }

      .fa-wind,
      .fa-cloud-showers-heavy,
      .fa-bug,
      .fa-water {
            color: rgb(0, 234, 255)
        }
        
     .bieudo {
      min-width: 310px;
      max-width: 800px;
      height: 400px;
      margin: 0 auto;
      display: flex;
      flex-wrap: wrap;
      justify-content: space-around;
      background-color: #f0f0f0;
      padding: 20px;
      border-radius: 10px;
      margin-bottom: 20px;
    }
    /*h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    } */
           
    </style>
</head>
<body>
    <!-- Script and setInterval code go here -->
    <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
    <script src="script.js"></script>
    <script>
        setInterval(function()
    {
      getDATAHval(); 
      getDATATval();
      getDATALval();
      getDATASMval();
      getTHOITIETval();
      getMTTHOITIETval();
      getICONTHOITIETval();
    
    }, 5000);
    //-------------------------------------------------------
    // doc do am 
    function getDATAHval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("HUMIvalue").innerHTML =
          this.responseText;
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readHUMI", true);
      DATAvalRequest.send();
    }
   
    // doc nhiet do 
    function getDATATval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("TEMPvalue").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readTEMP", true);
      DATAvalRequest.send();
    }

      // doc anh sang 
    function getDATALval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("LIGHTvalue").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readLIGHT", true);
      DATAvalRequest.send();
    }
   // doc do am dat 
    function getDATASMval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("SMvalue").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readSM", true);
      DATAvalRequest.send();
    }
    // doc du lieu thoi tiet
  function getTHOITIETval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("THOITIETvalue").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readTHOITIET", true);
      DATAvalRequest.send();
    }
    
  function getMTTHOITIETval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("MTTHOITIETvalue").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readMTTHOITIET", true);
      DATAvalRequest.send();
    }
    
  function getICONTHOITIETval()
    {
      var DATAvalRequest = new XMLHttpRequest();
      DATAvalRequest.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("iconTT").innerHTML =
          this.responseText;
        }
      };
      DATAvalRequest.open("GET", "readICON", true);
      DATAvalRequest.send();
    }

    // cong tac
   $(document).ready(function() {
      // Các hàm điều khiển đèn
      function readLightState() {
        $.ajax({
          url: "/readLightState",
          type: "GET",
          success: function(response) {
            var states = response.split(',');
            for (var i = 0; i < states.length; i++) {
              $("#toggleState" + (i + 1)).text(states[i]);
            }
          },
          error: function(error) {
            console.error("Error reading light state:", error);
          }
        });
      }

    function toggleLight(lightIndex) {
        $.ajax({
          url: "/toggleLight" + lightIndex,
          type: "POST",
          success: function(response) {
            readLightState(); // Cập nhật trạng thái đèn sau khi bật/tắt
          },
          error: function(error) {
            console.error("Error toggling light:", error);
          }
        });
      }

      // Khi trang web được tải, đọc và hiển thị trạng thái đèn
      readLightState();

      // Gọi hàm toggleLight khi click vào nút bật/tắt
      $("#toggleLight1").click(function() {
        toggleLight(1);
      });

      $("#toggleLight2").click(function() {
        toggleLight(2);
      });

      $("#toggleLight3").click(function() {
        toggleLight(3);
      });

      $("#toggleLight4").click(function() {
        toggleLight(4);
      });
    });

    
    </script>
    <header>
        <h1>....<i class="fas fa-truck"></i> TRANG TRAI THONG MINH <i class="fas fa-tree"></i></h1>
        <p>*****************************************************************</p>
    </header>
<div class="data">
    <div>
        <div class="data_child load-sensor-data">
            <h2><i class="fas fa-database"></i>Thoi tiet hom nay</h2>
            <p><i class="fas fa-carrot"></i>Dang theo doi thoi tiet...</p>
            <p><i class="fas fa-tint"></i> Du bao hoi tiet hom nay: <span id="THOITIETvalue"></span></p>
            <p>Mo ta thoi tiet : <span id="MTTHOITIETvalue"></span></p>
            <span id="iconTT"> <img src="http://openweathermap.org/img/w/04n.png" alt="Weather Icon"></span>
        </div>

        <div class="data_child sensor-data">
            <h2><i class="fas fa-database"></i> Du lieu cam bien </h2>
            <p><i class="fas fa-carrot"></i>Dang theo doi moi truong nong nghiep va du bao thoi tiet</p>
            <p><i class="fas fa-tint"></i> Do am: <span id="HUMIvalue">0</span>&#37;</p>
            <p><i class="fas fa-thermometer-half"></i> Nhiet do: <span id="TEMPvalue">0</span>&#8451;</p>
            <p><i class="fas fa-wind"></i> Anh sang: <span id="LIGHTvalue">0</span> Lux</p>
            <p><i class="fas fa-bug"></i> Do am dat: <span id="SMvalue">0</span>&#37;</p>
        </div>

    <div class="data_child toggle-container">
           <h2><i class="fas fa-toggle-on"></i> Cong tac</h2>
      
        <div class="toggle-switch-container">
           <div class="toggle-switch" id="toggle1">Den 1</div>
           <span class="toggle-state" id="toggleState1">OFF</span>
           <!-- Nút bật/tắt đèn 1 -->
           <button id="toggleLight1">Bat/Tat</button>
        </div>

        <div class="toggle-switch-container">
          <div class="toggle-switch" id="toggle2">Den 2</div>
          <span class="toggle-state" id="toggleState2">OFF</span>
          <!-- Nút bật/tắt đèn 2 -->
          <button id="toggleLight2">Bat/Tat</button>
        </div>

    <div class="toggle-switch-container">
          <div class="toggle-switch" id="toggle3">Den 3</div>
          <span class="toggle-state" id="toggleState3">OFF</span>
          <!-- Nút bật/tắt đèn 3 -->
          <button id="toggleLight3">Bat/Tat</button>
    </div>

    <div class="toggle-switch-container">
          <div class="toggle-switch" id="toggle4">Den 4</div>
          <span class="toggle-state" id="toggleState4">OFF</span>
          <!-- Nút bật/tắt đèn 4 -->
          <button id="toggleLight4">Bat/Tat</button>
    </div>
  </div>
</div>

<div class="bieudo">

  <h2 style ="color:#fff;text-shadow: 0 0 5px rgb(14, 247, 72);padding: 10px 0;" >Bieu do nhiet do, do am</h2>
  <div id="chart-temperature" class="container"></div>
  <div id="chart-humidity" class="container"></div>

  <script>
    var chartT = new Highcharts.Chart({
      chart:{ renderTo : 'chart-temperature' },
      title: { text: 'DHT11 Nhiet Do' },
      series: [{
        showInLegend: false,
        data: []
      }],
      plotOptions: {
        line: { animation: false,
          dataLabels: { enabled: true }
        },
        series: { color: '#059e8a' }
      },
      xAxis: { type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
      },
      yAxis: {
        title: { text: 'Nhiet do (do C)' }
      },
      credits: { enabled: false }
    });
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var x = (new Date()).getTime(),
              y = parseFloat(this.responseText);
          //console.log(this.responseText);
          // Áp dụng múi giờ của Việt Nam (UTC+7)
          x += 7 * 60 * 60 * 1000;
          
          if(chartT.series[0].data.length > 40) {
            chartT.series[0].addPoint([x, y], true, true, true);
          } else {
            chartT.series[0].addPoint([x, y], true, false, true);
          }
        }
      };
      xhttp.open("GET", "readTEMP", true);
      xhttp.send();
    }, 5000) ;
    
    var chartH = new Highcharts.Chart({
      chart:{ renderTo:'chart-humidity' },
      title: { text: 'DHT11 do am' },
      series: [{
        showInLegend: false,
        data: []
      }],
      plotOptions: {
        line: { animation: false,
          dataLabels: { enabled: true }
        }
      },
      xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
      },
      yAxis: {
        title: { text: 'Do am (%)' }
      },
      credits: { enabled: false }
    });
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var x = (new Date()).getTime(),
              y = parseFloat(this.responseText);
          //console.log(this.responseText);
           // Áp dụng múi giờ của Việt Nam (UTC+7)
          x += 7 * 60 * 60 * 1000;
          
          if(chartH.series[0].data.length > 40) {
            chartH.series[0].addPoint([x, y], true, true, true);
          } else {
            chartH.series[0].addPoint([x, y], true, false, true);
          }
        }
      };
      xhttp.open("GET", "readHUMI", true);
      xhttp.send();
    },5000 ) ;
    
  </script>
</div>


<footer class="footer">
  &copy; DUY MANH
</footer>
</body>

</html>


)***";