import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "IRentalProtocol";
const contractAddr = "0x5495bec6703adc6d395e50bb2c6a93bb4d2af56a";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Rental - Cancel Offer";  // <= Name of the test
const testDirSuffix = "rental-cancel-offer"; // <= directory to compare device snapshots to
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

// https://polygonscan.com/tx/0xc7c0d24f7989cf14507440eaeb7bf28ca56b3d37bd97e3bb396f043aa8618dbe
const inputData = "0x6e09f4200000000000000000000000000000000000000261ef6af322fdcfa610fcc3dac3";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
