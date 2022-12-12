import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "CraftHelper";
const contractAddr = "0xe29c9a493ede58028163ab04215e18a8acd0472c";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Craft Booster (5 cards)";  // <= Name of the test
const testDirSuffix = "craft_booster_5"; // <= directory to compare device snapshots to
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

// https://polygonscan.com/tx/0x5d57f6eccb4b14a5a854b0c07c70161d03392ea9c28c69c9e71a9ffeec5a0291
const inputData = "0xb60099b70000000000000000000000004d33b9c8a02ec9a892c98aa9561a3e743df1fea30000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041b4394f2a1a2eaf7e21460ef59370789cb1f42000000000000000000000000000000000000000000000054d58e4f7eee62d4d20000000000000000000000002b70b0ddb96e2581a311deb25a1424c7167e4a5300000000000000000000000000000000000000000000003e78a01a4c8dd5cb59000000000000000000000000000000000000000000000048ba70abe60810000a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000052fc543bd23d1948f11eb265eabdefbbb013157200000000000000000000000000000000000000000000001194afb1bf95a8d365000000000000000000000000f6351c1163314e95d025575c5cea314b055b7ed300000000000000000000000000000000000000000000000ce1b91e11a8b8a6d300000000000000000000000000000000000000000000000f07cf9afe0be8000a";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
