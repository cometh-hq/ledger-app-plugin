import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "GrindHelper";
const contractAddr = "0x91197719be34440a3bd0415fe293f4c19653a277";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Grind Card";  // <= Name of the test
const testDirSuffix = "grind_card"; // <= directory to compare device snapshots to
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

// https://polygonscan.com/tx/0xadcc927fc1d65cbf68211c599fdbe5dc50a8125d9e90e6e79513b8952a99e40e
const inputData = "0x54506e9200000000000000000000000000000000000000000010001650ba6ef6ea7b6ebe000000000000000000000000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041b4394f2a1a2eaf7e21460ef59370789cb1f420000000000000000000000002b70b0ddb96e2581a311deb25a1424c7167e4a53000000000000000000000000000000000000000000000000000000000000000000000000000000000000000052fc543bd23d1948f11eb265eabdefbbb0131572000000000000000000000000f6351c1163314e95d025575c5cea314b055b7ed3";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
