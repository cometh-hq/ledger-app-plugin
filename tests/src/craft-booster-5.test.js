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

// https://polygonscan.com/tx/0xaf9b0787ef2b37836402bb0ea04219824820396438c600efbc0c66849e97997c
const inputData = "0xb60099b7000000000000000000000000b835f2736a2bafafb8e4a250fe130dc08b74006e0000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041b4394f2a1a2eaf7e21460ef59370789cb1f42000000000000000000000000000000000000000000000053e22b6b7a5ecb5c400000000000000000000000002b70b0ddb96e2581a311deb25a1424c7167e4a5300000000000000000000000000000000000000000000003f227484d1b9d6d198000000000000000000000000000000000000000000000048ba70abe60810000a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000052fc543bd23d1948f11eb265eabdefbbb013157200000000000000000000000000000000000000000000001157a9cd4346f7d7d5000000000000000000000000f6351c1163314e95d025575c5cea314b055b7ed300000000000000000000000000000000000000000000000d0c600470f099bd6100000000000000000000000000000000000000000000000f07cf9afe0be8000a";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
