import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - Sublet";  // <= Name of the test
const testDirSuffix = "rental-sublet"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 7 + 2, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanox",
      label: "Nano X",
      steps: 7, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanosp",
      label: "Nano S+",
      steps: 7, // <= Define the number of steps for this test case and this device
  },
];

// https://polygonscan.com/tx/0xf4a7d20111df125b23efba03d818c376b8be21fdf6f788afd86d1707dd247d79
const inputData = "0x03388b4e00000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed91800000000000000000000000000000000000000000000000000000000000f444c000000000000000000000000eae707f06a65102d6ab4300a53a0ce63d6f1bcd70000000000000000000000000000000000000000000000000000000000000683";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
