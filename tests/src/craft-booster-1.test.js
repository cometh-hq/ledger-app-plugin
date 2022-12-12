import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "CraftHelper";
const contractAddr = "0xe29c9a493ede58028163ab04215e18a8acd0472c";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Craft Booster (1 card)";  // <= Name of the test
const testDirSuffix = "craft_booster_1"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 6 + 2, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanox",
      label: "Nano X",
      steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanosp",
      label: "Nano S+",
      steps: 6, // <= Define the number of steps for this test case and this device
  },
];

// https://polygonscan.com/tx/0x2b3a7e36f711ce32854bee27101e8a813e1395158c00462204d4badb059c9c5d
const inputData = "0xb60099b70000000000000000000000004d33b9c8a02ec9a892c98aa9561a3e743df1fea30000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041b4394f2a1a2eaf7e21460ef59370789cb1f4200000000000000000000000000000000000000000000001219141e9cc90ad81a0000000000000000000000002b70b0ddb96e2581a311deb25a1424c7167e4a5300000000000000000000000000000000000000000000000d53c294f8702d9c0c00000000000000000000000000000000000000000000000f83ef139ae300000a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000052fc543bd23d1948f11eb265eabdefbbb0131572000000000000000000000000000000000000000000000003afb139ea3c488f75000000000000000000000000f6351c1163314e95d025575c5cea314b055b7ed3000000000000000000000000000000000000000000000002b375443d8258440900000000000000000000000000000000000000000000000326cc8ffb761c000a";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
