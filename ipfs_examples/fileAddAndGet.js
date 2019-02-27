// import IPFS from 'ipfs';
const IPFS = require('ipfs');

//init node
const node = new IPFS();

//upload data to ipfs
let wirteData = (data, func) => {
    var buf = Buffer.from(JSON.stringify(data));
    node.files.add(buf, (err, files) => {
        // console.log(files)
        func(files[0]['hash']); //or files['path']
    });
}

//get data from ipfs
let getData = (hashPath, func) => {
    node.files.get(hashPath, (err, files) => {
        // console.log(files)
        func(files);
    });
}


//Examples
let testdata = {"name":"Catty", "age":20}

node.on('ready', () => {
    wirteData(testdata, (hashPath) => {
        console.log("hashPath: " + hashPath);

        getData(hashPath, (files) => {
            // console.log("files: " + files);
            console.log(JSON.parse(files[0].content.toString()));
            // stopping a node
            node.stop(() => {
                // node is now 'offline'
            });
        });
    });
}).on('error', (err) => {
    throw err;
});
