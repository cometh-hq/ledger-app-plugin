import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "BattleGameV2";
const contractAddr = "0xb44e1a7fee110f4af6c1b6d2c5ef324c5920f7d2";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Get Reward";  // <= Name of the test
const testDirSuffix = "rewards"; // <= directory to compare device snapshots to
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

// https://polygonscan.com/tx/0xf6392986fc6c6e5b0ede4c46afc68e3f09e87a06e2c336fdac1e28a5b8363da8
const inputData = "0x6363e8820000000000000000000000000000000000000000000000000000000000000020363330336631303766356236393631666635366433323561000000000000000000000000000000000000000085bc2e8aaad5dbc347db49ea45d95486279ed9180000000000000000000000005b6ca824b7c086ecc7a8f9de86c54d6bb15193b90000000000000000000000000000000000000000000000000000000002aea5d7000000000000000000000000b835f2736a2bafafb8e4a250fe130dc08b74006e0000000000000000000000000000000000000000000000000000000003dfd245000000000000000000000000b835f2736a2bafafb8e4a250fe130dc08b74006e0000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000004148feb15212f684133f8834f49ba2a624f91c4a4cd2eb9a3cb12d9f5ac89845360068343b80975c8d26d98c5049e645eaf178fa7ea99ca71218b56e49a82fd9121b00000000000000000000000000000000000000000000000000000000000000";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
