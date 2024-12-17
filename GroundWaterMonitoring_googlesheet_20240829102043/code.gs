function doPost(e) {
Logger.log("--- doPost ---");

var waterUsage = "",
waterYield = "";

try {
// Debugging helper
if (e == null){ 
e = {};
e.parameters = {waterUsage: "0", waterYield: "0"};
}

// Extract parameters from the request
waterUsage = e.parameters.waterUsage;
waterYield = e.parameters.waterYield;

// Save the data to spreadsheet
saveData(waterUsage, waterYield);

return ContentService.createTextOutput("Wrote:\n Water Usage: " + waterUsage + "\n Yield: " + waterYield);

} catch(error) { 
Logger.log(error); 
return ContentService.createTextOutput("Oops... " + error.message 
+ "\n" + new Date() 
+ "\nWater Usage: " + waterUsage +
"\nYield: " + waterYield);
} 
}

// Method to save given data to a sheet
function saveData(waterUsage, waterYield) {
Logger.log("--- saveData ---"); 

try {
var dateTime = new Date();

// Replace with your Google Sheets URL
var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/11t5CzNJrRU2W19qmdIsN0JGhbX4mv5Y9TW-ZDrSZJQA/edit?gid=0#gid=0");
var sheet = ss.getSheetByName("Datalogger");

// Get last edited row from DataLogger sheet
var row = sheet.getLastRow() + 1;

// Start Populating the data
sheet.getRange("A" + row).setValue(row - 1); // Number (Row ID)
sheet.getRange("B" + row).setValue(dateTime); // Date/Time
sheet.getRange("C" + row).setValue(waterUsage); // Water Usage
sheet.getRange("D" + row).setValue(waterYield); // Yield

} catch(error) {
Logger.log(JSON.stringify(error));
}

Logger.log("--- saveData end---"); 
}


