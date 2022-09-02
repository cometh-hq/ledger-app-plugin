import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - End Rental Prematurely";  // <= Name of the test
const testDirSuffix = "rental-end-rental-prematurely"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 5 + 1, // <= Define the number of steps for this test case and this device
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

// https://polygonscan.com/tx/0xd49428974a156df754864d7f961907775d7df5300af7cfdccad553e641339f98
const inputData = "0xe1649e8d00000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed91800000000000000000000000000000000000000000000000000000000006ad2ef";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
