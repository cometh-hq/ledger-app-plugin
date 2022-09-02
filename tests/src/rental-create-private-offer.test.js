import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - Create Private Offer";  // <= Name of the test
const testDirSuffix = "rental-create-private-offer"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 8 + 3, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanox",
      label: "Nano X",
      steps: 8, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanosp",
      label: "Nano S+",
      steps: 8, // <= Define the number of steps for this test case and this device
  },
];

// https://polygonscan.com/tx/0x1e36edf33de7d14af1da80bf09a2025a7effa1e5210fc32335d7225b9df1af58
const inputData = "0x1ae501840000000000000000000000000000000000000000000000000000000000000020000000000000000000000000b835f2736a2bafafb8e4a250fe130dc08b74006e000000000000000000000000472afd5a5303ac2799475687e943bba72846bd6b00000000000000000000000000000000000000000000000000000000000000e00000000000000000000000009c78ee466d6cb57a4d01fd887d2b5dfb2d46288f00000000000000000000000000000000000000000000002a1f0a87470e840000000000000000000000000000000000000000018c121725fff7f594b179a8b9b300000000000000000000000000000000000000000000000000000000631effea000000000000000000000000000000000000000000000000000000000000000100000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed9180000000000000000000000000000000000000000000000000000000003dfd2450000000000000000000000000000000000000000000000000000000000093a80000000000000000000000000000000000000000000000000000000000000076c";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
