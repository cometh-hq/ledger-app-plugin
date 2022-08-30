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

// https://polygonscan.com/tx/0xe7a60d9b37f5ed77bb97ef408da28ea21042310b98155cc12282920b7a55e34f
const inputData = "0xb60099b7000000000000000000000000502fce03af4bfd3dc991a6f7d0523cb920e1dbc80000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041b4394f2a1a2eaf7e21460ef59370789cb1f42000000000000000000000000000000000000000000000011e7c3642bf98e5cce0000000000000000000000002b70b0ddb96e2581a311deb25a1424c7167e4a5300000000000000000000000000000000000000000000000d7609d381597cc79a00000000000000000000000000000000000000000000000f83ef139ae300000a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000052fc543bd23d1948f11eb265eabdefbbb0131572000000000000000000000000000000000000000000000003a366244624f66692000000000000000000000000f6351c1163314e95d025575c5cea314b055b7ed3000000000000000000000000000000000000000000000002bc06b7348b7aab3300000000000000000000000000000000000000000000000326cc8ffb761c000a";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
