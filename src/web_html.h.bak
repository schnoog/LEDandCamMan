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
