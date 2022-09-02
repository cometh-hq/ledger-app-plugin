import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - End Sublet";  // <= Name of the test
const testDirSuffix = "rental-end-sublet"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanox",
      label: "Nano X",
      steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanosp",
      label: "Nano S+",
      steps: 5, // <= Define the number of steps for this test case and this device
  },
];

// https://polygonscan.com/tx/0x14f888c82e77142f9efc164e7d37f03361755efafe52e02a02a81a0dc52ee3b3
const inputData = "0x1beddfdd00000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed91800000000000000000000000000000000000000000000000000000000000f444c";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
