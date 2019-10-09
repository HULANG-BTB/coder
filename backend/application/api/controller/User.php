<?php
/**
 * FileName: Base.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 9:38
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */

namespace app\api\controller;

use app\common\controller\Base;
use think\App;
use think\Controller;
use think\facade\Session;
use think\Request;
use app\api\model\User as UserModel;

/**
 * Class User
 * Author: Hu Lang
 * DateTime: 2019/9/27 9:48
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * @package app\api\controller
 * Description:
 */
class User extends Base
{
    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new UserModel();
    }

    /**
     * Notes: 获取用户信息
     * DateTime: 2019/9/27 12:03
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     * @throws \think\Exception\DbException
     */
    public function getUserInfo() {
        $ret = [
            'code' => 0
        ];
        $uid = Session::get('uid');
        if (!isset($uid)) {
            $ret['data'] = null;
            return json($ret);
        }
        $user = $this->Model
            ->field(['username', 'email', 'school', 'submit', 'solved', 'language'])
            ->get($uid);
        if (!isset($user)) {
            return json($ret);
        }
        $ret['code'] = 1;
        $ret['data'] = $user;
        return json($ret);
    }


}
