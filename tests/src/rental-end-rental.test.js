import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - End Rental";  // <= Name of the test
const testDirSuffix = "rental-end-rental"; // <= directory to compare device snapshots to
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

// https://polygonscan.com/tx/0xfff519b0bf2ad9fbba6eedab04b6a7d3ffaf5072da465c2741ab489ba9cc3cd9
const inputData = "0x1157decb00000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed91800000000000000000000000000000000000000000000000000000000000f4596";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
