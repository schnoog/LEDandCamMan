const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>LED Color Control</title>
<style>
    body {
        font-family: Arial, sans-serif;
        margin: 20px;
    }
    #color-picker-container {
        margin-bottom: 20px;
    }
        #camera-container {
            position: relative;
            height: 450px; /* Added fixed height */
        }
        #camera-controls {
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
        }
        #camera-iframe {
            width: 100%;
            height: 100%;
            border: none;
            transform: rotate(180deg); /* Rotate iframe by 180 degrees */
        }
        .control-button {
            margin: 5px;
            padding: 10px;
            background-color: #f0f0f0;
            border: 1px solid #ccc;
            cursor: pointer;
        }
        #x-coordinate, #y-coordinate {
            margin-top: 10px;
        }    
</style>
</head>
<body>

<h1>LED Color Control</h1>

<div id="color-picker-container">
    <label for="color-picker">Select Color:</label>
    <input type="color" id="color-picker">
</div>

<div>
    <label for="brightness-slider">Brightness:</label>
    <input type="range" min="0" max="255" value="255" id="brightness-slider">
</div>

<button onclick="sendColor()">Set Color</button>
<hr>
    <div id="camera-container">
        <iframe id="camera-iframe" src="http://192.168.178.35/webcam/?action=stream"></iframe>
        <div id="camera-controls">
            <button class="control-button" onclick="moveCamera('up')">Up</button>
            <div>
                <button class="control-button" onclick="moveCamera('left')">Left</button>
                <button class="control-button" onclick="moveCamera('right')">Right</button>
            </div>
            <button class="control-button" onclick="moveCamera('down')">Down</button>
            <select id="step-selector">
                <option value="1">1</option>
                <option value="5">5</option>
                <option value="10">10</option>
            </select> <!-- Added dropdown field -->
            <button class="control-button" onclick="printCamera()">Print</button> <!-- Added print button -->
            <div id="x-coordinate">X Coordinate: <span id="x-value"></span></div>
            <div id="y-coordinate">Y Coordinate: <span id="y-value"></span></div>
            <button class="control-button" onclick="setPrintLocation()">Set New Print Location</button> <!-- Added set print location button -->
        </div>
    </div>

    <script>
        function moveCamera(direction) {
            var url = '/cam/pos';

            // Get current position
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        var response = xhr.responseText;
                        var pos = response.split(',');
                        var x = parseInt(pos[0]);
                        var y = parseInt(pos[1]);

                        // Modify position based on direction and step increment
                        var step = parseInt(document.getElementById('step-selector').value);
                        switch (direction) {
                            case 'up':
                                y = Math.max(0, y - step);
                                break;
                            case 'down':
                                y = Math.min(255, y + step);
                                break;
                            case 'left':
                                x = Math.max(0, x + step);
                                break;
                            case 'right':
                                x = Math.min(255, x - step);
                                break;
                        }

                        // Update camera position
                        var newPosition = '/cam/' + x + '/' + y;
                        console.log('New position:', newPosition);
                        // Send request to update camera position without changing page content
                        var updateRequest = new XMLHttpRequest();
                        updateRequest.open('GET', newPosition, true);
                        updateRequest.send();

                        // Update X and Y coordinate fields
                        document.getElementById('x-value').innerText = x;
                        document.getElementById('y-value').innerText = y;
                    } else {
                        console.error('Failed to get current position');
                    }
                }
            };
            xhr.open('GET', url, true);
            xhr.send();
        }
        
        function printCamera() {
            var printUrl = '/cam/print';
            var printRequest = new XMLHttpRequest();
            printRequest.open('GET', printUrl, true);
            printRequest.send();
        }

        function setPrintLocation() {
            var x = document.getElementById('x-value').innerText;
            var y = document.getElementById('y-value').innerText;
            var printXUrl = '/cam/printx/' + x;
            var printYUrl = '/cam/printy/' + y;
            
            var printXRequest = new XMLHttpRequest();
            printXRequest.open('GET', printXUrl, true);
            printXRequest.send();

            var printYRequest = new XMLHttpRequest();
            printYRequest.open('GET', printYUrl, true);
            printYRequest.send();
        }
    </script>

<script>
    function sendColor() {
        var colorPicker = document.getElementById('color-picker');
        var brightnessSlider = document.getElementById('brightness-slider');
        var hexColor = colorPicker.value.substring(1); // remove '#' from color value
        var brightness = brightnessSlider.value;

        // Convert hex color to RGB values
        var red = parseInt(hexColor.substring(0,2), 16);
        var green = parseInt(hexColor.substring(2,4), 16);
        var blue = parseInt(hexColor.substring(4,6), 16);

        var url = '/led/' + red + '/' + green + '/' + blue + '/' + brightness;

        // Call the URL
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    // Update color picker and brightness slider values based on the response
                    var response = xhr.responseText;
                    var values = response.split(',');

                    // Extract red, green, blue, and brightness values
                    var red = parseInt(values[0]);
                    var green = parseInt(values[1]);
                    var blue = parseInt(values[2]);
                    var brightness = parseInt(values[3]);

                    // Generate hex color code
                    var hexColor = '#' + ((1 << 24) + (red << 16) + (green << 8) + blue).toString(16).slice(1);

                    // Update color picker value
                    colorPicker.value = hexColor;

                    // Update brightness slider value
                    brightnessSlider.value = brightness;
                } else {
                    console.error('Failed to set LED color');
                }
            }
        };
        xhr.open('GET', url, true);
        xhr.send();
    }
</script>



</body>
</html>
)=====";
