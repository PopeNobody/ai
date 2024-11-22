#!node

const fs = require('fs');

var convs = require("./conversations.json");
var i;
fs.mkdirSync("conv");
for(i=0;i<convs.length;i++) {
  var fname="conv/conv_"+(1000+i)+".json";
  fs.writeFileSync(fname,JSON.stringify(convs[i],null,2));
};
console.log(`split into ${i} conversations`);
